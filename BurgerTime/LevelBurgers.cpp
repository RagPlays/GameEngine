#include <iostream>
#include <fstream>

#include "LevelBurgers.h"
#include "Burger.h"
#include "ResourceManager.h"

using namespace MoE;

LevelBurgers::LevelBurgers(GameObject* const owner, const std::string& burgerLoadPath)
	: Component{ owner }
{
	LoadBurgers(burgerLoadPath);
}

void LevelBurgers::Render() const
{
	for (const auto& burger : m_Burgers)
	{
		burger->Render();
	}
}

void LevelBurgers::CheckForCollision(const Recti& hitbox)
{
	for (auto& burger : m_Burgers)
	{
		burger->CheckForCollision(static_cast<Rectf>(hitbox));
	}
}

void LevelBurgers::LoadBurgers(const std::string& loadPath)
{
	const std::string pathName{ ResourceManager::Get().GetFullPath(loadPath) };

	if (std::ifstream inFile{ pathName }; !inFile.is_open())
	{
		std::cerr << "ERROR::LEVELBURGERS::COULD_NOT_LOAD_BURGERS_FROM_FILE: " << pathName << "\n";
		return;
	}
	else
	{
		// load the burgers
	}
}