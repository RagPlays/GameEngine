#include "InfoMenu.h"
#include "Timer.h"
#include "LevelManager.h"
#include "TextureRenderer.h"
#include "GameManager.h"
#include "GameObject.h"

InfoMenu::InfoMenu(MoE::GameObject* const owner)
	: Component{ owner }
	, m_CurrentWaitTime{}
	, m_TotalWaitTime{ 3.f }
{
}

void InfoMenu::SceneStart()
{
	if (MoE::TextureRenderer* renderComp{ GetOwner()->GetComponent<MoE::TextureRenderer>() }; renderComp)
	{
		const int scale{ GameManager::Get().GetGameScale() };
		renderComp->ScaleTextureDimensions(static_cast<float>(scale));
	}
}

void InfoMenu::Update()
{
	m_CurrentWaitTime += MoE::Timer::Get().GetElapsedSec();

	if (m_CurrentWaitTime >= m_TotalWaitTime)
	{
		LevelManager::Get().StartGame();
	}
}