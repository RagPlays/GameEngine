#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Renderer.h"

RenderComponent::RenderComponent(GameObject* const owner)
	: RenderComponent{ owner, std::shared_ptr<Texture2D>{} }
{
}

RenderComponent::RenderComponent(GameObject* const owner, std::shared_ptr<Texture2D> texture)
	: Component{ owner }
	, m_Texture{ texture }
	, m_RenderDimensions{}
	, m_SrcRectSet{ false }
	, m_SrcRect{}
{
	if (m_Texture != nullptr)
	{
		SetDefaultDimensions();
	}
}

void RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	if (texture != nullptr)
	{
		m_Texture = texture;
		SetDefaultDimensions();
	}
}

void RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture, const glm::ivec2& dimentions)
{
	if (texture != nullptr)
	{
		m_Texture = texture;
		SetTextureDimensions(dimentions);
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

void RenderComponent::SetTextureDimensions(const glm::ivec2& dimentions)
{
	m_RenderDimensions = dimentions;
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

	const Renderer& renderer{ Renderer::Get() };
	const glm::vec2& renderPos{ GetOwner()->GetWorldPosition() };
	const SDL_Rect destRect
	{ 
		static_cast<int>(renderPos.x),
		static_cast<int>(renderPos.y),
		m_RenderDimensions.x,
		m_RenderDimensions.y
	};

	if (m_SrcRectSet) renderer.RenderTexture(*m_Texture, destRect, m_SrcRect);
	else renderer.RenderTexture(*m_Texture, destRect);
}