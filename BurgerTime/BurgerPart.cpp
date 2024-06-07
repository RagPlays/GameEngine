#include "BurgerPart.h"
#include "Renderer.h"
#include "Collisions.h"
#include "TextureRenderer.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Structs.h"

BurgerPart::BurgerPart(MoE::GameObject* const owner, const glm::ivec2& dimentions)
	: Component{ owner }
	, m_Pushed{}
	, m_PushDistance{ 2.f * GameManager::Get().GetGameScale() }
	, m_Dimentions{ dimentions }
{
}

#if defined DEBUG || defined _DEBUG
void BurgerPart::Render() const
{
	const glm::vec2& position{ GetOwner()->GetWorldPosition() };
	const MoE::Recti destRect{ static_cast<glm::ivec2>(position), m_Dimentions };

	MoE::Renderer& renderer{ MoE::Renderer::Get() };

	renderer.SetCurrentDrawColor(MoE::Color{ 255, 0, 255 });
	renderer.RenderRect(static_cast<SDL_Rect>(destRect));
}
#endif

bool BurgerPart::GetIsPushed() const
{
	return m_Pushed;
}

void BurgerPart::CheckForCollision(const MoE::Rectf& hitbox)
{
	if (m_Pushed) return;
	const glm::vec2& position{ GetOwner()->GetWorldPosition() };
	const MoE::Rectf partHitbox{ position, static_cast<glm::vec2>(m_Dimentions) };
	if (MoE::Coll::OverLapping(hitbox, partHitbox))
	{
		m_Pushed = true;
		MoE::GameObject* burgerObjPtr{ GetOwner() };
		const glm::vec2 translation{ 0.f, m_PushDistance };
		burgerObjPtr->Translate(translation);
	}
}