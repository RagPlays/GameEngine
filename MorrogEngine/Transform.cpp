#include "Transform.h"

namespace MoE
{
	const glm::vec2& Transform::GetPosition() const
	{
		return m_Position;
	}

	void Transform::SetPosition(float x, float y)
	{
		m_Position = glm::vec2{ x, y };
	}

	void Transform::SetPosition(const glm::vec2& position)
	{
		m_Position = position;
	}
}