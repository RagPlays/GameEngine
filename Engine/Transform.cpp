#include "Transform.h"

const glm::vec3& Transform::GetPosition() const
{
	return m_Position;
}

void Transform::SetPosition(float x, float y, float z)
{
	m_Position = glm::vec3{ x, y, z };
}

void Transform::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}

const glm::vec3& Transform::GetRotation() const
{
	return m_Rotation;
}

void Transform::SetRotation(float x, float y, float z)
{
	m_Rotation = glm::vec3{ x, y, z };
}

void Transform::SetRotation(const glm::vec3& rotation)
{
	m_Rotation = rotation;
}

const glm::vec3& Transform::GetScale() const
{
	return m_Scale;
}

void Transform::SetScale(float x, float y, float z)
{
	m_Scale = glm::vec3{ x, y, z };
}

void Transform::setScale(const glm::vec3& scale)
{
	m_Scale = scale;
}