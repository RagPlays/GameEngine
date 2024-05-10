#include <iostream>
#include <cassert>

#include "LevelManager.h"
#include "LevelCollision.h"
#include "LevelRenderer.h"
#include "Level.h"
#include "GameObject.h"

void LevelManager::RegisterLevel(Level* level)
{
    if (m_pCurrentLevel == nullptr)
    {
        m_pCurrentLevel = level;

        GameObject* gameObj{ level->GetOwner() };
        if (LevelCollision* coll{ gameObj->GetComponent<LevelCollision>() }; coll)
        {
            m_pCurrentLevelCollision = coll;
        }
        else
        {
            std::cerr << "ERROR::LEVELMANAGER::NO_COLLISION_IN_LEVEL\n";
        }
        if (LevelRenderer* rend{ gameObj->GetComponent<LevelRenderer>() }; rend)
        {
            m_pCurrentLevelRenderer = rend;
        }
        else
        {
            std::cerr << "ERROR::LEVELMANAGER::NO_RENDERER_IN_LEVEL\n";
        }
        return;
    }
    std::cerr << "ERROR::LEVELMANAGER::UNABLE_TO_REGISTER_LEVEL\n";
    assert(false);
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

Level* LevelManager::GetLevel() const
{
    return m_pCurrentLevel;
}

LevelRenderer* LevelManager::GetRenderer() const
{
    return m_pCurrentLevelRenderer;
}

LevelCollision* LevelManager::GetCollision() const
{
    return m_pCurrentLevelCollision;
}