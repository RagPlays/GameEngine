#include "WaitMenu.h"
#include "Timer.h"
#include "LevelManager.h"
#include "TextureRenderer.h"
#include "GameManager.h"
#include "GameObject.h"

WaitMenu::WaitMenu(MoE::GameObject* const owner, float waitTime, bool startMenu)
	: Component{ owner }
	, m_CurrentWaitTime{}
	, m_TotalWaitTime{ waitTime }
	, m_StartMenu{ startMenu }
{
}

void WaitMenu::SceneStart()
{
	if (MoE::TextureRenderer* renderComp{ GetOwner()->GetComponent<MoE::TextureRenderer>() }; renderComp)
	{
		const int scale{ GameManager::Get().GetGameScale() };
		renderComp->ScaleTextureDimensions(static_cast<float>(scale));
	}
}

void WaitMenu::Update()
{
	m_CurrentWaitTime += MoE::Timer::Get().GetElapsedSec();

	if (m_CurrentWaitTime >= m_TotalWaitTime)
	{
		if (m_StartMenu)
		{
			LevelManager::Get().GoStartMenu();
		}
		else
		{
			LevelManager::Get().StartGame();
		}
	}
}