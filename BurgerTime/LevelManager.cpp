#include <iostream>
#include <cassert>

#include "LevelManager.h"
#include "Level.h"
#include "LevelRenderer.h"
#include "LevelCollision.h"
#include "LevelBurgers.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "EventIDs.h"

using namespace MoE;

void LevelManager::RegisterLevel(Level* const level)
{
    if (!level) return;
    if (m_pCurrentLevel)
    {
        std::cerr << "ERROR::LEVELMANAGER::UNABLE_TO_REGISTER_LEVEL\n";
        return;
    }
    m_pCurrentLevel = level;
}

void LevelManager::UnRegisterLevel(Level* const level)
{
    if (!level) return;
    if (m_pCurrentLevel == level)
    {
        m_pCurrentLevel = nullptr;
        m_pCurrentLevelCollision = nullptr;
        m_pCurrentLevelRenderer = nullptr;
        m_pCurrentLevelBurgers = nullptr;
        return;
    }
    std::cerr << "ERROR::LEVELMANAGER::UNABLE_TO_UNREGISTER_LEVEL\n";
    assert(false);
}

void LevelManager::SetGameMode(GameMode gameMode)
{
    if (m_CurrentLevel)
    {
        std::cerr << "ERROR::LEVELMANAGER::CANT_CHANGE_GAMEMODE_INSIDE_LEVEL\n";
        return;
    }
    m_GameMode = gameMode;
}

GameMode LevelManager::GetGameMode() const
{
    return m_GameMode;
}

void LevelManager::GoStartMenu()
{
    SceneManager::Get().SetCurrentSceneByName("StartMenuScene");
}

void LevelManager::StartGame()
{
    m_CurrentLevel = 0;
    SceneManager::Get().SetCurrentSceneByIndex(static_cast<uint8_t>(m_CurrentLevel));
}

void LevelManager::GoInfoMenu()
{
    SceneManager::Get().SetCurrentSceneByName("InfoMenuScene");
}

void LevelManager::NextLevel()
{
    if (m_CurrentLevel != -1)
    {
        const uint8_t currentLevel{ static_cast<uint8_t>(m_CurrentLevel) };
        const uint8_t nextLevelIdx{ static_cast<uint8_t>((currentLevel + 1) % m_NrLevelsCount) };
        SceneManager::Get().SetCurrentSceneByIndex(nextLevelIdx);
        m_CurrentLevel = nextLevelIdx;
    }
}

void LevelManager::GameOver()
{
    SceneManager::Get().SetCurrentSceneByName("EndMenuScene");
}

uint8_t LevelManager::GetTileSize() const
{
    return m_TileSize;
}

Level* LevelManager::GetLevel() const
{
    return m_pCurrentLevel;
}

LevelRenderer* LevelManager::GetRenderer()
{
    if (!m_pCurrentLevelRenderer && m_pCurrentLevel)
    {
        m_pCurrentLevelRenderer = m_pCurrentLevel->GetOwner()->GetComponent<LevelRenderer>();
    }
    return m_pCurrentLevelRenderer;
}

LevelCollision* LevelManager::GetCollision()
{
    if (!m_pCurrentLevelCollision && m_pCurrentLevel)
    {
        m_pCurrentLevelCollision = m_pCurrentLevel->GetOwner()->GetComponent<LevelCollision>();
    }
    return m_pCurrentLevelCollision;
}

LevelBurgers* LevelManager::GetBurgers()
{
    if (!m_pCurrentLevelBurgers && m_pCurrentLevel)
    {
        m_pCurrentLevelBurgers = m_pCurrentLevel->GetOwner()->GetComponent<LevelBurgers>();
    }
    return m_pCurrentLevelBurgers;
}

LevelManager::LevelManager()
    : Subject{}
    , m_GameMode{ GameMode::singlePlayer }
    , m_CurrentLevel{}
    , m_NrLevelsCount{ 3 }
    , m_TileSize{ 16 }
    , m_pCurrentLevel{}
    , m_pCurrentLevelRenderer{}
    , m_pCurrentLevelCollision{}
    , m_pCurrentLevelBurgers{}
{
    assert(m_NrLevelsCount);
}