#include <iostream>
#include <cassert>

#include "LevelManager.h"
#include "LevelCollision.h"
#include "LevelRenderer.h"
#include "Level.h"
#include "GameObject.h"

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
    , m_TileSize{ 16 }
{
}