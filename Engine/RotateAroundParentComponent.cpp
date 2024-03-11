#include <numbers>
#include <glm.hpp>
#include "RotateAroundParentComponent.h"
#include "GameObject.h"
#include "Timer.h"

RotateAroundParentComponent::RotateAroundParentComponent(GameObject* const owner, float rotationSpeed)
	: Component{ owner }
	, m_RotationSpeed{ rotationSpeed }
	, m_CurrentAngle{}
{
}

void RotateAroundParentComponent::Update()
{
	constexpr float fullCirlce{ static_cast<float>(std::numbers::pi) * 2.f };

	if (GetParent())
	{
		if (m_CurrentAngle >= fullCirlce)
		{
			m_CurrentAngle -= fullCirlce;
		}

		const float radius{ glm::length(GetLocalPosition()) };
		m_CurrentAngle += m_RotationSpeed * Timer::Get().GetElapsedSec();

		SetLocalPosition({ radius * std::cosf(m_CurrentAngle), radius * std::sinf(m_CurrentAngle), 0.f });
	}
}