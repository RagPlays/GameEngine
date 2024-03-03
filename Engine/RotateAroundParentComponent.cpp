#include <glm/glm.hpp>
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
	if (GetParent())
	{
		const float radius{ glm::length(GetLocalPosition()) };
		m_CurrentAngle += m_RotationSpeed * Timer::GetInstance().GetElapsedSec();

		SetLocalPosition({ radius * std::cosf(m_CurrentAngle), radius * std::sinf(m_CurrentAngle), 0.f });
	}
}