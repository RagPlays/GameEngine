#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

GameObject::~GameObject() = default;

void GameObject::FixedUpdate(float)
{
}

void GameObject::Update(float)
{
}

void GameObject::LateUpdate(float)
{
}

void GameObject::Render() const
{
	const glm::vec3& renderPos{ m_transform.GetPosition() };
	Renderer::GetInstance().RenderTexture(*m_texture, renderPos.x, renderPos.y);
}

void GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}