#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>
#include <memory>

//////// Engine ////////
// Defaults
#include "Engine.h"
#include "Scene.h"
#include "GameObject.h"
// Singletons
#include "SceneManager.h"
#include "ServiceLocator.h"
#include "Timer.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "InputStructs.h"
#include "InputCodes.h"
#include "EventQueue.h"
#include "SoundSystem.h"
// Components
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FpsComponent.h"
////////////////////////

//////// Game Specific ////////
// Singletons
#include "GameManager.h"
#include "LevelManager.h"
// Components
#include "LevelRenderer.h"
#include "LevelCollision.h"
#include "Level.h"
#include "Player.h"
#include "PlayerMovement.h"
// InputCommands
#include "PlayerMoveCommand.h"
#include "PlayerStopCommand.h"
#include "NextLevelCommand.h"
// Sound
#include "SoundEventHandler.h"
#include "SoundIDs.h"

using namespace MoE;

inline static void LoadLevelOne(Scene& scene)
{
	// Get References
	ResourceManager& resourceManager{ ResourceManager::Get() };
	InputManager& input{ InputManager::Get() };
	const int gameScale{ GameManager::Get().GetGameScale() };

	// Loading In
	std::shared_ptr<Texture2D> levelTileMap{ resourceManager.LoadTexture("Textures/TileMap.png") };
	std::shared_ptr<Texture2D> playerSpriteSheet{ resourceManager.LoadTexture("Textures/PlayerSpriteSheet.png") };

	std::shared_ptr<Font> fpsFont{ resourceManager.LoadFont("Lingua.otf", 13 * gameScale) };

	// FPS panel
	std::unique_ptr<GameObject> fpsCounter{ std::make_unique<GameObject>() };
	fpsCounter->AddComponent<RenderComponent>(
		std::make_unique<RenderComponent>(fpsCounter.get()));

	fpsCounter->AddComponent<TextComponent>(
		std::make_unique<TextComponent>(fpsCounter.get(), fpsFont));

	fpsCounter->AddComponent<FpsComponent>(
		std::make_unique<FpsComponent>(fpsCounter.get()));


	// Level
	std::unique_ptr<GameObject> level{ std::make_unique<GameObject>() };
	level->AddComponent<LevelRenderer>(
		std::make_unique<LevelRenderer>(level.get(), "Saves/Level1/RenderData.morrog", levelTileMap));

	level->AddComponent<LevelCollision>(
		std::make_unique<LevelCollision>(level.get(), "Saves/Level1/CollisionData.morrog"));

	level->AddComponent<Level>(
		std::make_unique<Level>(level.get()));

	// Player(s)
	std::unique_ptr<GameObject> pcPlayer{ std::make_unique<GameObject>() };
	pcPlayer->AddComponent<RenderComponent>(
		std::make_unique<RenderComponent>(pcPlayer.get(), playerSpriteSheet));

	pcPlayer->AddComponent<Player>(
		std::make_unique<Player>(pcPlayer.get()));

	pcPlayer->AddComponent<PlayerMovement>(
		std::make_unique<PlayerMovement>(pcPlayer.get()));

	Player* kInputPlayerComp{ pcPlayer->GetComponent<Player>() };
	// Input
	// Up
	KeyBoardInput kGoUpInput{ KeyBoardButton::KB_W, InputType::ispressed };
	KeyBoardInput kStopUpInput{ KeyBoardButton::KB_W, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> kPlayerUp{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::ivec2{0, -1}) };
	std::unique_ptr<PlayerStopCommand> kPlayerStopUp{ std::make_unique<PlayerStopCommand>(kInputPlayerComp, glm::ivec2{0, -1}) };
	// Left
	KeyBoardInput kGoLeftInput{ KeyBoardButton::KB_A, InputType::ispressed };
	KeyBoardInput kStopLeftInput{ KeyBoardButton::KB_A, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> kPlayerLeft{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::ivec2{-1, 0}) };
	std::unique_ptr<PlayerStopCommand> kPlayerStopLeft{ std::make_unique<PlayerStopCommand>(kInputPlayerComp, glm::ivec2{-1, 0}) };
	// Down
	KeyBoardInput kGoDownInput{ KeyBoardButton::KB_S, InputType::ispressed };
	KeyBoardInput kStopDownInput{ KeyBoardButton::KB_S, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> kPlayerDown{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::ivec2{0, 1}) };
	std::unique_ptr<PlayerStopCommand> kPlayerStopDown{ std::make_unique<PlayerStopCommand>(kInputPlayerComp, glm::ivec2{0, 1}) };
	// Right
	KeyBoardInput kGoRightInput{ KeyBoardButton::KB_D, InputType::ispressed };
	KeyBoardInput kStopRightInput{ KeyBoardButton::KB_D, InputType::wasReleasedThisFrame };
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

	// Next Level //
	KeyBoardInput kGoNextLevel{ KeyBoardButton::KB_C, InputType::wasPressedThisFrame };
	std::unique_ptr<NextLevelCommand> kNextLevel{ std::make_unique<NextLevelCommand>() };
	input.AddKeyboardMouseBind(kGoNextLevel, std::move(kNextLevel));

	// Add To Scene
	scene.Add(std::move(level));
	scene.Add(std::move(pcPlayer));

	scene.Add(std::move(fpsCounter));
}

inline static void LoadLevelTwo(Scene& scene)
{
	std::cout << "Loading Level Two\n";

	// Get References
	ResourceManager& resourceManager{ ResourceManager::Get() };

	// Level
	std::shared_ptr<Texture2D> levelTileMap{ resourceManager.LoadTexture("Textures/TileMap.png") };
	std::unique_ptr<GameObject> level{ std::make_unique<GameObject>() };
	level->AddComponent<LevelRenderer>(
		std::make_unique<LevelRenderer>(level.get(), "Saves/Level1/RenderData.morrog", levelTileMap));

	level->AddComponent<LevelCollision>(
		std::make_unique<LevelCollision>(level.get(), "Saves/Level1/CollisionData.morrog"));

	level->AddComponent<Level>(
		std::make_unique<Level>(level.get()));

	scene.Add(std::move(level));
}

inline static void LoadLevelThree(Scene&)
{
	std::cout << "Loading Level Three\n";

	// Get References
	//ResourceManager& resourceManager{ ResourceManager::Get() };
	//InputManager& input{ InputManager::Get() };
}

inline static void AddScenes()
{
	SceneManager& sceneM{ SceneManager::Get() };
	sceneM.CreateScene("LevelOneScene", LoadLevelOne);
	sceneM.CreateScene("LevelTwoScene", LoadLevelTwo);
	sceneM.CreateScene("LevelThreeScene", LoadLevelThree);
}

int main(int, char*[]) 
{
	const glm::ivec2& windowSize{ GameManager::Get().GetWindowSize() };
	MoE::Engine engine("../Resources/", windowSize.x, windowSize.y);
	AddScenes();

	// mouse cursor //
#if defined _DEBUG || defined DEBUG
	engine.SetShowCursor(true);
#else
	//engine.SetShowCursor(false);
#endif

	engine.Run();

    return 0;
}