#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

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
	, m_RenderDimentions{ glm::ivec2{} }
{
	if (m_Texture.get())
	{
		SetDefaultDimentions();
	}
}

void RenderComponent::SetTextureFromFileName(const std::string& fileName)
{
	SetTexture(ResourceManager::GetInstance().LoadTexture(fileName));
}

void RenderComponent::SetTexture(std::shared_ptr<Texture2D> newTexture)
{
	if (newTexture.get())
	{
		m_Texture = newTexture;
		SetDefaultDimentions();
	}
}

void RenderComponent::SetDefaultDimentions()
{
	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &m_RenderDimentions.x, &m_RenderDimentions.y);
}

void RenderComponent::SetTextureWidth(int width)
{
	m_RenderDimentions.x = width;
}

void RenderComponent::SetTextureHeight(int height)
{
	m_RenderDimentions.y = height;
}

void RenderComponent::SetTextureDimentions(int width, int height)
{
	m_RenderDimentions.x = width;
	m_RenderDimentions.y = height;
}

void RenderComponent::SetTextureDimentions(const glm::ivec2& dimentions)
{
	SetTextureDimentions(dimentions.x, dimentions.y);
}

void RenderComponent::Render() const
{
	if (m_Texture.get())
	{
		const glm::vec3& renderPos{ GetOwner()->GetPosition() };
		Renderer::GetInstance().RenderTexture(*m_Texture, static_cast<int>(renderPos.x), static_cast<int>(renderPos.y), m_RenderDimentions.x, m_RenderDimentions.y);
	}
}