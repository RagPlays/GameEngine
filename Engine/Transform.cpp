#include "Transform.h"

const glm::vec3& Transform::GetPosition() const
{
	return m_position;
}

void Transform::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

const glm::vec3& Transform::GetScale() const
{
	return m_Scale;
}

void Transform::SetScale(float x, float y, float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
}