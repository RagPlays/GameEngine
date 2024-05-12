#include <iostream>

#include "GameManager.h"

const int GameManager::GetGameScale() const
{
	return m_GameScale;
}

const glm::ivec2& GameManager::GetWindowSize() const
{
	return m_WindowSize;
}

GameManager::GameManager()
	: m_GameScale{ 3 } // min 1, max 15!
	, m_DefaultWindowSize{ 240, 240 }
	, m_WindowSize{ m_DefaultWindowSize * m_GameScale } // I know I know... dw
{
}