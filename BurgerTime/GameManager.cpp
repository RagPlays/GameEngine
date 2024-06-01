#include <iostream>

#include "GameManager.h"

GameManager::GameManager()
	: m_GameScale{ 3 }
	, m_DefaultWindowSize{ 240, 240 }
	, m_WindowSize{ m_DefaultWindowSize * m_GameScale } // I know I know... dw
{
}

int GameManager::GetGameScale() const
{
	return m_GameScale;
}

const glm::ivec2& GameManager::GetWindowSize() const
{
	return m_WindowSize;
}