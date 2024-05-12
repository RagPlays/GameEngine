#include <iostream>
#include <cassert>

#include "LevelManager.h"
#include "LevelCollision.h"
#include "LevelRenderer.h"
#include "Level.h"
#include "GameObject.h"
#include "SceneManager.h"

using namespace MoE;

void LevelManager::RegisterLevel(Level* level)
{
    if (m_pCurrentLevel)
    {
        std::cerr << "ERROR::LEVELMANAGER::UNABLE_TO_REGISTER_LEVEL\n";
        return;
    }
    m_pCurrentLevel = level;
}

void LevelManager::UnRegisterLevel(Level* level)
{
    if (m_pCurrentLevel == level)
    {
        m_pCurrentLevel = nullptr;
        m_pCurrentLevelCollision = nullptr;
        m_pCurrentLevelRenderer = nullptr;
        return;
    }
    std::cerr << "ERROR::LEVELMANAGER::UNABLE_TO_UNREGISTER_LEVEL\n";
    assert(false);
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

LevelManager::LevelManager()
    : m_pCurrentLevel{ nullptr }
    , m_pCurrentLevelRenderer{ nullptr }
    , m_pCurrentLevelCollision{ nullptr }
    , m_CurrentLevel{ 0 }
    , m_NrLevelsCount{ 3 }
    , m_TileSize{ 16 }
{
    assert(m_NrLevelsCount);
}