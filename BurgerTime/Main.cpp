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
#include "PlayerStateHandler.h"
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
	// Get References //
	ResourceManager& resourceManager{ ResourceManager::Get() };
	InputManager& input{ InputManager::Get() };
	const int gameScale{ GameManager::Get().GetGameScale() };

	// Loading In //
	std::shared_ptr<Texture2D> levelTileMap{ resourceManager.LoadTexture("Textures/TileMap.png") };
	std::shared_ptr<Texture2D> playerSpriteSheet{ resourceManager.LoadTexture("Textures/PlayerSpriteSheet.png") };
	std::shared_ptr<Font> fpsFont{ resourceManager.LoadFont("Lingua.otf", 13 * gameScale) };

	// FPS panel //
	std::unique_ptr<GameObject> fpsCounter{ std::make_unique<GameObject>() };

	// Create Components
	auto fpsCounterRenderComp{ std::make_unique<RenderComponent>(fpsCounter.get()) };
	auto fpsCounterTextComp{ std::make_unique<TextComponent>(fpsCounter.get(), fpsFont) };
	auto fpsCounterFpsComp{ std::make_unique<FpsComponent>(fpsCounter.get()) };

	// Add Components
	fpsCounter->AddComponent<RenderComponent>(std::move(fpsCounterRenderComp));
	fpsCounter->AddComponent<TextComponent>(std::move(fpsCounterTextComp));
	fpsCounter->AddComponent<FpsComponent>(std::move(fpsCounterFpsComp));

	// Level //
	std::unique_ptr<GameObject> level{ std::make_unique<GameObject>() };

	// Create Components
	auto levelLevelRenderer{ std::make_unique<LevelRenderer>(level.get(), "Saves/Level1/RenderData.morrog", levelTileMap) };
	auto levelLevelCollision{ std::make_unique<LevelCollision>(level.get(), "Saves/Level1/CollisionData.morrog") };
	auto levelLevel{ std::make_unique<Level>(level.get()) };

	// Add Components
	level->AddComponent<LevelRenderer>(std::move(levelLevelRenderer));
	level->AddComponent<LevelCollision>(std::move(levelLevelCollision));
	level->AddComponent<Level>(std::move(levelLevel));

	// Player(s) //
	std::unique_ptr<GameObject> pcPlayer{ std::make_unique<GameObject>() };

	// Create Components
	auto pcPlayerRenderComp{ std::make_unique<RenderComponent>(pcPlayer.get(), playerSpriteSheet) };
	auto pcPlayerPlayer{ std::make_unique<Player>(pcPlayer.get()) };
	Player* kInputPlayerComp{ pcPlayerPlayer.get() };
	auto pcPlayerPlayerStateHandler{ std::make_unique<PlayerStateHandler>(pcPlayer.get(), kInputPlayerComp) };

	// Add Components
	pcPlayer->AddComponent<RenderComponent>(std::move(pcPlayerRenderComp));
	pcPlayer->AddComponent<Player>(std::move(pcPlayerPlayer));
	pcPlayer->AddComponent<PlayerStateHandler>(std::move(pcPlayerPlayerStateHandler));

	// Input
	// Up
	KeyBoardInput kGoUpInput{ KeyBoardButton::KB_W, InputType::ispressed };
	KeyBoardInput kStopUpInput{ KeyBoardButton::KB_W, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> kPlayerUp{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::ivec2{0, -1}) };
	std::unique_ptr<PlayerStopCommand> kPlayerStopUp{ std::make_unique<PlayerStopCommand>(kInputPlayerComp, glm::ivec2{0, -1}) };
	KeyBoardInput kGoUpInput2{ KeyBoardButton::KB_UP, InputType::ispressed };
	KeyBoardInput kStopUpInput2{ KeyBoardButton::KB_UP, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> kPlayerUp2{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::ivec2{0, -1}) };
	std::unique_ptr<PlayerStopCommand> kPlayerStopUp2{ std::make_unique<PlayerStopCommand>(kInputPlayerComp, glm::ivec2{0, -1}) };
	// Left
	KeyBoardInput kGoLeftInput{ KeyBoardButton::KB_A, InputType::ispressed };
	KeyBoardInput kStopLeftInput{ KeyBoardButton::KB_A, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> kPlayerLeft{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::ivec2{-1, 0}) };
	std::unique_ptr<PlayerStopCommand> kPlayerStopLeft{ std::make_unique<PlayerStopCommand>(kInputPlayerComp, glm::ivec2{-1, 0}) };
	KeyBoardInput kGoLeftInput2{ KeyBoardButton::KB_LEFT, InputType::ispressed };
	KeyBoardInput kStopLeftInput2{ KeyBoardButton::KB_LEFT, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> kPlayerLeft2{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::ivec2{-1, 0}) };
	std::unique_ptr<PlayerStopCommand> kPlayerStopLeft2{ std::make_unique<PlayerStopCommand>(kInputPlayerComp, glm::ivec2{-1, 0}) };
	// Down
	KeyBoardInput kGoDownInput{ KeyBoardButton::KB_S, InputType::ispressed };
	KeyBoardInput kStopDownInput{ KeyBoardButton::KB_S, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> kPlayerDown{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::ivec2{0, 1}) };
	std::unique_ptr<PlayerStopCommand> kPlayerStopDown{ std::make_unique<PlayerStopCommand>(kInputPlayerComp, glm::ivec2{0, 1}) };
	KeyBoardInput kGoDownInput2{ KeyBoardButton::KB_DOWN, InputType::ispressed };
	KeyBoardInput kStopDownInput2{ KeyBoardButton::KB_DOWN, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> kPlayerDown2{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::ivec2{0, 1}) };
	std::unique_ptr<PlayerStopCommand> kPlayerStopDown2{ std::make_unique<PlayerStopCommand>(kInputPlayerComp, glm::ivec2{0, 1}) };
	// Right
	KeyBoardInput kGoRightInput{ KeyBoardButton::KB_D, InputType::ispressed };
	KeyBoardInput kStopRightInput{ KeyBoardButton::KB_D, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> kPlayerRight{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::ivec2{1, 0}) };
	std::unique_ptr<PlayerStopCommand> kPlayerStopRight{ std::make_unique<PlayerStopCommand>(kInputPlayerComp, glm::ivec2{1, 0}) };
	KeyBoardInput kGoRightInput2{ KeyBoardButton::KB_RIGHT, InputType::ispressed };
	KeyBoardInput kStopRightInput2{ KeyBoardButton::KB_RIGHT, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> kPlayerRight2{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::ivec2{1, 0}) };
	std::unique_ptr<PlayerStopCommand> kPlayerStopRight2{ std::make_unique<PlayerStopCommand>(kInputPlayerComp, glm::ivec2{1, 0}) };

	// Add Binds
	// Up
	input.AddKeyboardMouseBind(kGoUpInput, std::move(kPlayerUp));
	input.AddKeyboardMouseBind(kStopUpInput, std::move(kPlayerStopUp));
	input.AddKeyboardMouseBind(kGoUpInput2, std::move(kPlayerUp2));
	input.AddKeyboardMouseBind(kStopUpInput2, std::move(kPlayerStopUp2));
	// Left
	input.AddKeyboardMouseBind(kGoLeftInput, std::move(kPlayerLeft));
	input.AddKeyboardMouseBind(kStopLeftInput, std::move(kPlayerStopLeft));
	input.AddKeyboardMouseBind(kGoLeftInput2, std::move(kPlayerLeft2));
	input.AddKeyboardMouseBind(kStopLeftInput2, std::move(kPlayerStopLeft2));
	// Down
	input.AddKeyboardMouseBind(kGoDownInput, std::move(kPlayerDown));
	input.AddKeyboardMouseBind(kStopDownInput, std::move(kPlayerStopDown));
	input.AddKeyboardMouseBind(kGoDownInput2, std::move(kPlayerDown2));
	input.AddKeyboardMouseBind(kStopDownInput2, std::move(kPlayerStopDown2));
	// Right
	input.AddKeyboardMouseBind(kGoRightInput, std::move(kPlayerRight));
	input.AddKeyboardMouseBind(kStopRightInput, std::move(kPlayerStopRight));
	input.AddKeyboardMouseBind(kGoRightInput2, std::move(kPlayerRight2));
	input.AddKeyboardMouseBind(kStopRightInput2, std::move(kPlayerStopRight2));

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