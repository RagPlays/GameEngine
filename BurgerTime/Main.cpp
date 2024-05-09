#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>
#include <memory>

#include "Engine.h"

//#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "Timer.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "EventQueue.h"

#include "Scene.h"
#include "GameObject.h"

#include "RenderComponent.h"
#include "TextComponent.h"
#include "FpsComponent.h"
#include "RotateAroundParentComponent.h"
#include "PlayerComponent.h"
#include "PlayerStatsComponent.h"

#include "LevelRenderer.h"
#include "LevelCollision.h"

#include "PlayerMoveCommand.h"
#include "PlayerStopCommand.h"

#include "SoundEventHandler.h"

#include "SoundSystem.h"
#include "SoundIDs.h"

void LoadLevelOne(Scene& scene)
{
	std::cout << "Loading Level One\n";

	// Get References
	ResourceManager& resourceManager{ ResourceManager::Get() };
	InputManager& input{ InputManager::Get() };

	// Loading In
	std::shared_ptr<Texture2D> levelTileMap{ resourceManager.LoadTexture("Textures/TileMap.png") };
	std::shared_ptr<Texture2D> playerSpriteSheet{ resourceManager.LoadTexture("burgerTimePlayer.png") };

	// Level
	std::unique_ptr<GameObject> level{ std::make_unique<GameObject>() };
	level->AddComponent<LevelRenderer>(std::make_unique<LevelRenderer>(level.get(), "Saves/Level1/RenderData.morrog", levelTileMap));
	level->AddComponent<LevelCollision>(std::make_unique<LevelCollision>(level.get(), "Saves/Level1/CollisionData.morrog"));

	// Player(s)
	std::unique_ptr<GameObject> pcPlayer{ std::make_unique<GameObject>() };
	pcPlayer->AddComponent<RenderComponent>(
		std::make_unique<RenderComponent>(pcPlayer.get(), playerSpriteSheet));

	pcPlayer->AddComponent<PlayerComponent>(
		std::make_unique<PlayerComponent>(pcPlayer.get()));

	pcPlayer->AddComponent<PlayerMovementComponent>(
		std::make_unique<PlayerMovementComponent>(pcPlayer.get(), 100.f));

	PlayerMovementComponent* kInputPlayerComp{ pcPlayer->GetComponent<PlayerMovementComponent>() };
	// Input
	// Up
	KeyBoardInput kGoUpInput{ SDL_SCANCODE_W, InputType::ispressed };
	KeyBoardInput kStopUpInput{ SDL_SCANCODE_W, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> kPlayerUp{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::ivec2{0, -1}) };
	std::unique_ptr<PlayerStopCommand> kPlayerStopUp{ std::make_unique<PlayerStopCommand>(kInputPlayerComp, glm::ivec2{0, -1}) };
	// Left
	KeyBoardInput kGoLeftInput{ SDL_SCANCODE_A, InputType::ispressed };
	KeyBoardInput kStopLeftInput{ SDL_SCANCODE_A, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> kPlayerLeft{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::ivec2{-1, 0}) };
	std::unique_ptr<PlayerStopCommand> kPlayerStopLeft{ std::make_unique<PlayerStopCommand>(kInputPlayerComp, glm::ivec2{-1, 0}) };
	// Down
	KeyBoardInput kGoDownInput{ SDL_SCANCODE_S, InputType::ispressed };
	KeyBoardInput kStopDownInput{ SDL_SCANCODE_S, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> kPlayerDown{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::ivec2{0, 1}) };
	std::unique_ptr<PlayerStopCommand> kPlayerStopDown{ std::make_unique<PlayerStopCommand>(kInputPlayerComp, glm::ivec2{0, 1}) };
	// Right
	KeyBoardInput kGoRightInput{ SDL_SCANCODE_D, InputType::ispressed };
	KeyBoardInput kStopRightInput{ SDL_SCANCODE_D, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> kPlayerRight{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::ivec2{1, 0}) };
	std::unique_ptr<PlayerStopCommand> kPlayerStopRight{ std::make_unique<PlayerStopCommand>(kInputPlayerComp, glm::ivec2{1, 0}) };

	// Add Binds
	// Up
	input.AddKeyboardMouseBind(kGoUpInput, std::move(kPlayerUp));
	input.AddKeyboardMouseBind(kStopUpInput, std::move(kPlayerStopUp));
	// Left
	input.AddKeyboardMouseBind(kGoLeftInput, std::move(kPlayerLeft));
	input.AddKeyboardMouseBind(kStopLeftInput, std::move(kPlayerStopLeft));
	// Down
	input.AddKeyboardMouseBind(kGoDownInput, std::move(kPlayerDown));
	input.AddKeyboardMouseBind(kStopDownInput, std::move(kPlayerStopDown));
	// Right
	input.AddKeyboardMouseBind(kGoRightInput, std::move(kPlayerRight));
	input.AddKeyboardMouseBind(kStopRightInput, std::move(kPlayerStopRight));

	// Add To Scene
	scene.Add(std::move(level));
	scene.Add(std::move(pcPlayer));
}

void LoadLevelTwo(Scene&)
{
	std::cout << "Loading Level Two\n";

	// Get References
	//ResourceManager& resourceManager{ ResourceManager::Get() };
	//InputManager& input{ InputManager::Get() };
}

void LoadLevelThree(Scene&)
{
	std::cout << "Loading Level Three\n";

	// Get References
	//ResourceManager& resourceManager{ ResourceManager::Get() };
	//InputManager& input{ InputManager::Get() };
}

void AddScenes()
{
	SceneManager& sceneM{ SceneManager::Get() };
	sceneM.CreateScene("LevelOneScene", LoadLevelOne);
	sceneM.CreateScene("LevelTwoScene", LoadLevelTwo);
	sceneM.CreateScene("LevelThreeScene", LoadLevelThree);
}

int main(int, char*[]) 
{
	constexpr int windowWidth{ 240 * 3 }; // Game scaling 3 from original
	constexpr int windowHeight{ 240 * 3 };

	Engine engine("../Resources/", windowWidth, windowHeight);
	AddScenes();

	engine.Run();

    return 0;
}