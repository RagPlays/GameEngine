#include "BurgerPart.h"
#include "Renderer.h"
#include "Collisions.h"
#include "TextureRenderer.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Structs.h"

float BurgerPart::s_PushDistance{};

BurgerPart::BurgerPart(MoE::GameObject* const owner, const glm::ivec2& dimentions)
	: Component{ owner }
	, m_Pushed{}
	, m_Dimentions{ dimentions }
{
	s_PushDistance = 2.f * GameManager::Get().GetGameScale();
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

float BurgerPart::GetPushDistance()
{
	return s_PushDistance;
}

bool BurgerPart::GetIsPushed() const
{
	return m_Pushed;
}

void BurgerPart::UnPush()
{
	if (m_Pushed)
	{
		m_Pushed = false;
		const glm::vec2 translation{ 0.f, -s_PushDistance };
		GetOwner()->Translate(translation);
	}
}

bool BurgerPart::CheckForCollision(const MoE::Recti& hitbox)
{
	if (m_Pushed) return false;
	const glm::vec2& position{ GetOwner()->GetWorldPosition() };
	const MoE::Recti partHitbox{ static_cast<glm::ivec2>(position), m_Dimentions };
	if (MoE::Coll::OverLapping(hitbox, partHitbox))
	{
		m_Pushed = true;
		MoE::GameObject* burgerObjPtr{ GetOwner() };
		const glm::vec2 translation{ 0.f, s_PushDistance };
		burgerObjPtr->Translate(translation);
		return true;
	}
	return false;
}