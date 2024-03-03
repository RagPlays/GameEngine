#include <stdexcept>
#include "FpsComponent.h"
#include "GameObject.h"
#include "Timer.h"
#include "TextComponent.h"

FpsComponent::FpsComponent(GameObject* const owner)
	: Component{ owner }
	, m_NeedsUpdate{ true }
	, m_FrameCount{}
	, m_TotalWaitTime{}
	, m_UpdateTickTime{ 0.5f }
{
}

void FpsComponent::Update()
{
	++m_FrameCount;
	m_TotalWaitTime += Timer::GetInstance().GetElapsedSec();

	if (m_TotalWaitTime >= m_UpdateTickTime)
	{
		std::shared_ptr<TextComponent> textComponent{ GetOwner()->GetComponent<TextComponent>() };

		if (textComponent)
		{
			const float fpsAverage{ 1.f / (m_TotalWaitTime / m_FrameCount) };
			textComponent->SetText(std::format("{:.1f}", fpsAverage) + " FPS");
		}

		m_NeedsUpdate = false;

		m_TotalWaitTime -= m_UpdateTickTime;
		m_FrameCount = 0;
	}
}