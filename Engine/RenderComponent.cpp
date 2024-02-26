#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

RenderComponent::RenderComponent(GameObject* const owner)
	: RenderComponent{ owner, std::shared_ptr<Texture2D>{} }
{
}

RenderComponent::RenderComponent(GameObject* const owner, const std::string& fileName)
	: RenderComponent{ owner, ResourceManager::GetInstance().LoadTexture(fileName) }
{
}

RenderComponent::RenderComponent(GameObject* const owner, std::shared_ptr<Texture2D> texture)
	: Component{ owner }
	, m_Texture{ texture }
{
}

void RenderComponent::SetTextureFromFileName(const std::string& fileName)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(fileName);
}

void RenderComponent::SetTexture(std::shared_ptr<Texture2D> newTexture)
{
	m_Texture = newTexture;
}

void RenderComponent::Render() const
{
	if (m_Texture.get())
	{
		const glm::vec3& renderPos{ GetOwner()->GetPosition() };
		Renderer::GetInstance().RenderTexture(*m_Texture, renderPos.x, renderPos.y);
	}
}