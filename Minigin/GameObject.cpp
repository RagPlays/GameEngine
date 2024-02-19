#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

namespace dae
{
	GameObject::~GameObject() = default;

	void GameObject::Update()
	{

	}

	void GameObject::Render() const
	{
		const glm::vec3& renderPos{ m_transform.GetPosition() };
		Renderer::GetInstance().RenderTexture(*m_texture, renderPos.x, renderPos.y);
	}

	void dae::GameObject::SetTexture(const std::string& filename)
	{
		m_texture = ResourceManager::GetInstance().LoadTexture(filename);
	}

	void dae::GameObject::SetPosition(float x, float y)
	{
		m_transform.SetPosition(x, y, 0.0f);
	}

}