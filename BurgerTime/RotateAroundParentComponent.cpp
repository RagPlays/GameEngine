#include <numbers>
#include <glm.hpp>

#include "RotateAroundParentComponent.h"
#include "GameObject.h"
#include "Timer.h"

using namespace MoE;

RotateAroundParentComponent::RotateAroundParentComponent(GameObject* const owner, float rotationSpeed)
	: Component{ owner }
	, m_RotationSpeed{ rotationSpeed }
	, m_CurrentAngle{}
{
}

void RotateAroundParentComponent::Update()
{
	constexpr float fullCirlce{ static_cast<float>(std::numbers::pi) * 2.f };

	GameObject* owner{ GetOwner() };

	if (owner->GetParent())
	{
		if (m_CurrentAngle >= fullCirlce)
		{
			m_CurrentAngle -= fullCirlce;
		}

		const float radius{ glm::length(owner->GetLocalPosition()) };
		m_CurrentAngle += m_RotationSpeed * Timer::Get().GetElapsedSec();

		owner->SetLocalPosition({ radius * std::cosf(m_CurrentAngle), radius * std::sinf(m_CurrentAngle) });
	}
}