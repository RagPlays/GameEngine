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
	: RenderComponent{ owner, ResourceManager::Get().LoadTexture(fileName) }
{
}

RenderComponent::RenderComponent(GameObject* const owner, std::shared_ptr<Texture2D> texture)
	: Component{ owner }
	, m_Texture{ texture }
	, m_RenderDimensions{ glm::ivec2{} }
	, m_SrcRectSet{ false }
	, m_SrcRect{}
{
	if (m_Texture.get())
	{
		SetDefaultDimensions();
	}
}

void RenderComponent::SetTextureFromFileName(const std::string& fileName)
{
	SetTexture(ResourceManager::Get().LoadTexture(fileName));
}

void RenderComponent::SetTexture(std::shared_ptr<Texture2D> newTexture)
{
	if (newTexture.get())
	{
		m_Texture = newTexture;
		SetDefaultDimensions();
	}
}

void RenderComponent::SetDefaultDimensions()
{
	SDL_QueryTexture(m_Texture->GetSDLTexture(), nullptr, nullptr, &m_RenderDimensions.x, &m_RenderDimensions.y);
}

void RenderComponent::SetTextureWidth(int width)
{
	m_RenderDimensions.x = width;
}

void RenderComponent::SetTextureHeight(int height)
{
	m_RenderDimensions.y = height;
}

void RenderComponent::SetTextureDimensions(int width, int height)
{
	m_RenderDimensions.x = width;
	m_RenderDimensions.y = height;
}

void RenderComponent::SetTextureDimensions(const glm::ivec2& dimentions)
{
	SetTextureDimensions(dimentions.x, dimentions.y);
}

int RenderComponent::GetTextureWidth() const
{
	return m_RenderDimensions.x;
}

int RenderComponent::GetTextureHeight() const
{
	return  m_RenderDimensions.y;
}

const glm::ivec2& RenderComponent::GetTextureDimentions() const
{
	return m_RenderDimensions;
}

void RenderComponent::ClearSourceRect()
{
	m_SrcRect = SDL_Rect{};
	m_SrcRectSet = false;
}

void RenderComponent::SetSourceRect(int x, int y, int width, int height)
{
	SetSourceRect({ x, y, width, height });
}

void RenderComponent::SetSourceRect(const SDL_Rect& srcRect)
{
	m_SrcRect = srcRect;
	m_SrcRectSet = true;
}

void RenderComponent::Render() const
{
	if (!m_Texture) return;

	const glm::vec3& renderPos{ GetOwner()->GetWorldPosition() };
	const SDL_Rect destRect{ static_cast<int>(renderPos.x),  static_cast<int>(renderPos.y), m_RenderDimensions.x, m_RenderDimensions.y };

	if (m_SrcRectSet)
	{
		Renderer::Get().RenderTexture(*m_Texture, m_SrcRect, destRect);
	}
	else
	{
		Renderer::Get().RenderTexture(*m_Texture, destRect);
	}
}