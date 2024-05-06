#include "Transform.h"

Transform::Transform()
	: m_Position{}
	, m_Rotation{}
	, m_Scale{ 1.f, 1.f }
{
}

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

const glm::vec2& Transform::GetRotation() const
{
	return m_Rotation;
}

void Transform::SetRotation(float x, float y)
{
	m_Rotation = glm::vec2{ x, y };
}

void Transform::SetRotation(const glm::vec2& rotation)
{
	m_Rotation = rotation;
}

const glm::vec2& Transform::GetScale() const
{
	return m_Scale;
}

void Transform::SetScale(float x, float y)
{
	m_Scale = glm::vec2{ x, y };
}

void Transform::SetScale(const glm::vec2& scale)
{
	m_Scale = scale;
}