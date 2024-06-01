#include "Animation.h"
#include "Timer.h"
#include "TextureRenderer.h"

Animation::Animation(MoE::TextureRenderer* renderComponent, uint8_t nrOfFrames, uint8_t fps)
	: m_IsPlaying{ false }
	, m_CurrentFrame{ 0 }
	, m_NrOfFrames{ nrOfFrames }
	, m_FPS{ fps }
	, m_LastFrameTime{ 0.f }
	, m_pRenderComponent{ renderComponent }
	, m_SrcRects{ static_cast<size_t>(nrOfFrames) }
{
}

void Animation::AddFrame(const SDL_Rect& srcRect)
{
	m_SrcRects.emplace_back(srcRect);
}

void Animation::Play()
{
	if (m_IsPlaying || m_SrcRects.empty()) return;
	m_CurrentFrame = 0;
	m_pRenderComponent->SetSourceRect(m_SrcRects[m_CurrentFrame]);
	m_LastFrameTime = 0.f;
	m_IsPlaying = true;
}

bool Animation::Update()
{
	if (m_IsPlaying)
	{
		if (m_SrcRects.empty()) return false;
		else if (m_SrcRects.size() == 1) return false;

		m_LastFrameTime += MoE::Timer::Get().GetElapsedSec();

		const float secPerFrame{ 1.f / static_cast<float>(m_FPS) };
		if (m_LastFrameTime > secPerFrame)
		{
			m_CurrentFrame = (m_CurrentFrame + 1) % m_NrOfFrames;
			m_pRenderComponent->SetSourceRect(m_SrcRects[m_CurrentFrame]);
			m_LastFrameTime -= secPerFrame;
			if (m_CurrentFrame == 0) return true;
		}
	}
	return false;
}

void Animation::Stop(bool reset)
{
	if (!m_IsPlaying) return;
	if (reset)
	{
		m_CurrentFrame = 0;
		m_pRenderComponent->SetSourceRect(m_SrcRects[m_CurrentFrame]);
	}
	m_IsPlaying = false;
}