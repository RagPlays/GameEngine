#include <stdexcept>

#include "FpsComponent.h"
#include "GameObject.h"
#include "Timer.h"
#include "FontRenderer.h"

namespace MoE
{
	FpsComponent::FpsComponent(GameObject* const owner)
		: Component{ owner }
		, m_FrameCount{}
		, m_TotalWaitTime{}
		, m_UpdateTickTime{ 0.5f }
	{
	}

	void FpsComponent::SceneStart()
	{
		if (FontRenderer* const textComponent{ GetOwner()->GetComponent<FontRenderer>() })
		{
			textComponent->SetRenderForQuality(true);
			textComponent->SetText("Loading...");
		}
	}

	void FpsComponent::Update()
	{
		++m_FrameCount;
		const float thisFrameTime{ Timer::Get().GetElapsedSec() };
		m_TotalWaitTime += thisFrameTime;

		if (m_TotalWaitTime >= m_UpdateTickTime)
		{
			const float fpsAverage{ 1.f / (m_TotalWaitTime / m_FrameCount) };

			if (FontRenderer* const textComponent{ GetOwner()->GetComponent<FontRenderer>() })
			{
				textComponent->SetText(std::format("{:.1f}", fpsAverage) + " FPS");
			}

			m_TotalWaitTime -= m_UpdateTickTime;
			m_FrameCount = 0;
		}
	}
}