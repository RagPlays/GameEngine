#include <SDL.h>

#include "BurgerPart.h"
#include "Renderer.h"
#include "Collisions.h"
#include "TextureRenderer.h"
#include "GameManager.h"

BurgerPart::BurgerPart(const MoE::Rectf& hitbox, std::shared_ptr<MoE::Texture2D> texture, const MoE::Recti& srcRect)
	: m_Texture{ texture }
	, m_SrcRect{ srcRect }
	, m_Pushed{}
	, m_PushDistance{ 5.f * GameManager::Get().GetGameScale() }
	, m_Hitbox{ hitbox }
{
}

void BurgerPart::Render() const
{
	if (!m_Texture) return;

	MoE::Renderer& renderer{ MoE::Renderer::Get() };

	renderer.RenderTexture(*m_Texture, static_cast<SDL_Rect>(m_Hitbox), static_cast<SDL_Rect>(m_SrcRect));
}

bool BurgerPart::GetIsPushed() const
{
	return m_Pushed;
}

void BurgerPart::CheckForCollision(const MoE::Rectf& hitbox)
{
	if (m_Pushed) return;
	if (MoE::Coll::OverLapping(hitbox, m_Hitbox))
	{
		m_Pushed = true;
		m_Hitbox.pos.y -= m_PushDistance;
	}
}