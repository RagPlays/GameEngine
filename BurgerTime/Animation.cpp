#include "Animation.h"
#include "Timer.h"
#include "TextureRenderer.h"

Animation::Animation(MoE::TextureRenderer* renderComponent, uint8_t nrOfFrames, uint8_t fps)
	: m_IsPlaying{}
	, m_CurrentFrame{}
	, m_NrOfFrames{ nrOfFrames }
	, m_FPS{ fps }
	, m_LastFrameTime{}
	, m_pRenderComponent{ renderComponent }
	, m_SrcRects{}
{
	m_SrcRects.reserve(static_cast<size_t>(nrOfFrames));
}

void Animation::AddFrame(const MoE::Recti& srcRect)
{
	m_SrcRects.emplace_back(srcRect);
}

void Animation::Play()
{
	m_CurrentFrame = 0;
	m_LastFrameTime = 0.f;
	if (m_IsPlaying || m_SrcRects.empty()) return;
	m_pRenderComponent->SetSourceRect(m_SrcRects[m_CurrentFrame]);
	m_IsPlaying = true;
}

bool Animation::Update()
{
	if (m_IsPlaying && !m_SrcRects.empty())
	{
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