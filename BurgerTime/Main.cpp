#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

// ^(?([^\r\n])\s)*[^\s+?/]+[^\n]*$ // is for finding number of lines in project

#include <memory>
#include <functional>

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
#include "TextureRenderer.h"
#include "FontRenderer.h"
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
#include "PlayerHealthStats.h"
#include "PlayerStateHandler.h"
// InputCommands
#include "PlayerMoveCommand.h"
#include "PlayerStopCommand.h"
#include "PlayerAttackCommand.h"
#include "KillPlayerCommand.h"
#include "NextLevelCommand.h"
#include "WinLevelCommand.h"
#include "ReloadSceneCommand.h"
#include "StartGameCommand.h"
#include "ListNavCommand.h"
#include "ListPressCommand.h"
// Sounds
#include "SoundEventHandler.h"
#include "SoundIDs.h"
// UI
#include "ListSelection.h"
#include "Button.h"
#include "InfoMenu.h"

using namespace MoE;

// Helper Load Functions //
inline static void LoadPcPlayer(Scene& scene)
{
	InputManager& input{ InputManager::Get() };

	std::shared_ptr<Texture2D> playerSpriteSheet{ ResourceManager::Get().LoadTexture("Textures/PlayerSpriteSheet.png") };

	// Player(s) //
	std::unique_ptr<GameObject> pcPlayer{ std::make_unique<GameObject>() };

	// Create Components
	auto pcPlayerRenderComp{ std::make_unique<TextureRenderer>(pcPlayer.get(), playerSpriteSheet) };
	auto pcPlayerPlayer{ std::make_unique<Player>(pcPlayer.get()) };
	Player* kInputPlayerComp{ pcPlayerPlayer.get() };
	auto pcPlayerPlayerStateHandler{ std::make_unique<PlayerStateHandler>(pcPlayer.get(), kInputPlayerComp) };

	// Add Components
	pcPlayer->AddComponent<TextureRenderer>(std::move(pcPlayerRenderComp));
	pcPlayer->AddComponent<Player>(std::move(pcPlayerPlayer));
	pcPlayer->AddComponent<PlayerStateHandler>(std::move(pcPlayerPlayerStateHandler));

	// Player Health
	std::unique_ptr<GameObject> playerHealthStats{ std::make_unique<GameObject>() };
	auto pcPlayerHealthStats{ std::make_unique<PlayerHealthStats>(playerHealthStats.get(), kInputPlayerComp, static_cast<uint8_t>(3)) };
	playerHealthStats->AddComponent(std::move(pcPlayerHealthStats));

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

	// Attack
	KeyBoardInput kAttackInput{ KeyBoardButton::KB_E, InputType::wasPressedThisFrame };
	std::unique_ptr<PlayerAttackCommand> kPlayerAttack{ std::make_unique<PlayerAttackCommand>(kInputPlayerComp) };

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
	// Attack
	input.AddKeyboardMouseBind(kAttackInput, std::move(kPlayerAttack));

#if defined DEBUG || defined _DEBUG

	// Next Level //
	KeyBoardInput kGoNextLevel{ KeyBoardButton::KB_C, InputType::wasReleasedThisFrame };
	std::unique_ptr<NextLevelCommand> kGoNextLevelC{ std::make_unique<NextLevelCommand>() };
	input.AddKeyboardMouseBind(kGoNextLevel, std::move(kGoNextLevelC));

	// Win Level //
	KeyBoardInput kWinLevel{ KeyBoardButton::KB_Z, InputType::wasReleasedThisFrame };
	std::unique_ptr<WinLevelCommand> kWinLevelC{ std::make_unique<WinLevelCommand>() };
	input.AddKeyboardMouseBind(kWinLevel, std::move(kWinLevelC));

	// Kill Player //
	KeyBoardInput kKillPlayer{ KeyBoardButton::KB_K, InputType::wasReleasedThisFrame };
	std::unique_ptr<KillPlayerCommand> kKillPlayerC{ std::make_unique<KillPlayerCommand>(kInputPlayerComp) };
	input.AddKeyboardMouseBind(kKillPlayer, std::move(kKillPlayerC));

	// Reload Level //
	KeyBoardInput kReloadScene{ KeyBoardButton::KB_R, InputType::wasReleasedThisFrame };
	std::unique_ptr<ReloadSceneCommand> kReloadSceneC{ std::make_unique<ReloadSceneCommand>() };
	input.AddKeyboardMouseBind(kReloadScene, std::move(kReloadSceneC));

#endif

	scene.Add(std::move(pcPlayer));
	scene.Add(std::move(playerHealthStats));
}

inline static void LoadControllerPlayer(Scene&)
{

}

inline static void LoadFPSCounter(Scene& scene)
{
	const int gameScale{ GameManager::Get().GetGameScale() };

	std::shared_ptr<Font> fpsFont{ ResourceManager::Get().LoadFont("Lingua.otf", 8 * gameScale) };

	// FPS panel //
	std::unique_ptr<GameObject> fpsCounter{ std::make_unique<GameObject>() };

	// Create Components
	auto fpsCounterTextComp
	{
		std::make_unique<FontRenderer>(fpsCounter.get(), fpsFont)
	};
	auto fpsCounterFpsComp
	{
		std::make_unique<FpsComponent>(fpsCounter.get())
	};

	// Add Components
	fpsCounter->AddComponent<FontRenderer>(std::move(fpsCounterTextComp));
	fpsCounter->AddComponent<FpsComponent>(std::move(fpsCounterFpsComp));

	scene.Add(std::move(fpsCounter));
}

inline static void LoadLevel(Scene& scene, const std::string& levelPath)
{
	std::shared_ptr<Texture2D> levelTileMap{ ResourceManager::Get().LoadTexture("Textures/TileMap.png")};

	// Level //
	std::unique_ptr<GameObject> level{ std::make_unique<GameObject>() };

	// Create Components
	auto levelLevelRenderer
	{
		std::make_unique<LevelRenderer>(level.get(), "Saves/" + levelPath + "/RenderData.morrog", levelTileMap)
	};
	auto levelLevelCollision
	{
		std::make_unique<LevelCollision>(level.get(), "Saves/" + levelPath +"/CollisionData.morrog")
	};

	// auto levelBurgers

	// auto levelEnemies // ONLY FOR SINGLEPAYER!

	auto levelLevel
	{
		std::make_unique<Level>(level.get())
	};

	// Add Components
	level->AddComponent<LevelRenderer>(std::move(levelLevelRenderer));
	level->AddComponent<LevelCollision>(std::move(levelLevelCollision));
	level->AddComponent<Level>(std::move(levelLevel));

	scene.Add(std::move(level));
}

inline static void LoadMultiplayerLevel(Scene& scene, const std::string& levelPath)
{
	LoadLevel(scene, levelPath);
	LoadPcPlayer(scene);
	LoadControllerPlayer(scene);
	LoadFPSCounter(scene);
}

inline static void LoadSingleplayerLevel(Scene& scene, const std::string& levelPath)
{
	LoadLevel(scene, levelPath);
	LoadPcPlayer(scene);
	LoadFPSCounter(scene);
}

// Scene Load Functions //
inline static void LoadLevelOne(Scene& scene)
{
	std::cout << "Loading Level One\n";

	const std::string levelPath{ "Level1" };

	switch (LevelManager::Get().GetGameMode())
	{
	case GameMode::singlePlayer:
		LoadSingleplayerLevel(scene, levelPath);
		break;
	case GameMode::multiplayer:
		LoadMultiplayerLevel(scene, levelPath);
		break;
	}
}

inline static void LoadLevelTwo(Scene& scene)
{
	std::cout << "Loading Level Two\n";

	const std::string levelPath{ "Level2" };

	switch (LevelManager::Get().GetGameMode())
	{
	case GameMode::singlePlayer:
		LoadSingleplayerLevel(scene, levelPath);
		break;
	case GameMode::multiplayer:
		LoadMultiplayerLevel(scene, levelPath);
		break;
	}
}

inline static void LoadLevelThree(Scene& scene)
{
	std::cout << "Loading Level Three\n";

	const std::string levelPath{ "Level2" };

	switch (LevelManager::Get().GetGameMode())
	{
	case GameMode::singlePlayer:
		LoadSingleplayerLevel(scene, levelPath);
		break;
	case GameMode::multiplayer:
		LoadMultiplayerLevel(scene, levelPath);
		break;
	}
}

inline static void LoadStartMenu(Scene& scene)
{
	std::cout << "Loading Start Menu\n";

	InputManager& input{ InputManager::Get() };
	ResourceManager& resM{ ResourceManager::Get() };

	const auto markerTexture{ resM.LoadTexture("Textures/UI/Marker.png") };
	const auto playerButtonTex{ resM.LoadTexture("Textures/UI/PlayerButton.png") };
	const auto playersButtonTex{ resM.LoadTexture("Textures/UI/PlayersButton.png") };

	const int gameScale{ GameManager::Get().GetGameScale() };
	const glm::ivec2& windowSize{ GameManager::Get().GetWindowSize() };

	// Title //
	const auto titleTexture{ resM.LoadTexture("Textures/UI/TitleTexture.png") };
	std::unique_ptr<GameObject> startMenuTitle{ std::make_unique<GameObject>() };
	auto titleRenderer{ std::make_unique<TextureRenderer>(startMenuTitle.get(), titleTexture) };
	titleRenderer->ScaleTextureDimensions(static_cast<float>(gameScale));
	const glm::ivec2& dim{ titleRenderer->GetTextureDimentions() };
	const glm::vec2 titlePos{ (windowSize.x / 2) - (dim.x / 2), (windowSize.y / 4) - (dim.y / 2) };
	startMenuTitle->SetLocalPosition(titlePos);
	startMenuTitle->AddComponent<TextureRenderer>(std::move(titleRenderer));

	// UI //
	// List
	std::unique_ptr<GameObject> listSelectionUI{ std::make_unique<GameObject>() };
	auto list{ std::make_unique<ListSelection>(listSelectionUI.get(), false, 8 * gameScale, markerTexture, static_cast<int>(windowSize.y / 2.5f)) };
	auto listPtr{ list.get() };
	
	// 1 player button
	std::unique_ptr<GameObject> playerButtonObj{ std::make_unique<GameObject>() };

	auto playerRenderComp{ std::make_unique<TextureRenderer>(playerButtonObj.get(), playerButtonTex) };
	playerRenderComp->ScaleTextureDimensions(static_cast<float>(gameScale));

	std::function<void()> playerButtonFunc
	{
		[]() -> void
		{
			LevelManager::Get().SetGameMode(GameMode::singlePlayer);
#if defined DEBUG || defined _DEBUG
			LevelManager::Get().StartGame();
#else
			LevelManager::Get().GoInfoMenu();
#endif
		}
	};
	auto playerButton{ std::make_unique<Button>(playerButtonObj.get(), std::move(playerButtonFunc)) };

	playerButtonObj->AddComponent<TextureRenderer>(std::move(playerRenderComp));
	playerButtonObj->AddComponent<Button>(std::move(playerButton));

	list->AddButton(std::move(playerButtonObj));

	// 2 players button
	std::unique_ptr<GameObject> playersButtonObj{ std::make_unique<GameObject>() };

	auto playersRenderComp{ std::make_unique<TextureRenderer>(playersButtonObj.get(), playersButtonTex) };
	playersRenderComp->ScaleTextureDimensions(static_cast<float>(gameScale));

	std::function<void()> playersButtonFunc
	{
		[]() -> void
		{
			LevelManager::Get().SetGameMode(GameMode::multiplayer);
#if defined DEBUG || defined _DEBUG
			LevelManager::Get().StartGame();
#else
			LevelManager::Get().GoInfoMenu();
#endif
		}
	};
	auto playersButton{ std::make_unique<Button>(playersButtonObj.get(), std::move(playersButtonFunc)) };

	playersButtonObj->AddComponent<TextureRenderer>(std::move(playersRenderComp));
	playersButtonObj->AddComponent<Button>(std::move(playersButton));

	list->AddButton(std::move(playersButtonObj));

	listSelectionUI->AddComponent<ListSelection>(std::move(list));

	// Input //
	// Enter
	KeyBoardInput kPressButton{ KeyBoardButton::KB_RETURN, InputType::wasReleasedThisFrame };
	std::unique_ptr<ListPressCommand> kPressC{ std::make_unique<ListPressCommand>(listPtr) };
	input.AddKeyboardMouseBind(kPressButton, std::move(kPressC));
	// Up
	KeyBoardInput kUpButton{ KeyBoardButton::KB_UP, InputType::wasReleasedThisFrame };
	std::unique_ptr<ListNavCommand> kUpC{ std::make_unique<ListNavCommand>(listPtr, true) };
	KeyBoardInput kUpButton2{ KeyBoardButton::KB_W, InputType::wasReleasedThisFrame };
	std::unique_ptr<ListNavCommand> kUpC2{ std::make_unique<ListNavCommand>(listPtr, true) };
	input.AddKeyboardMouseBind(kUpButton, std::move(kUpC));
	input.AddKeyboardMouseBind(kUpButton2, std::move(kUpC2));
	// Down
	KeyBoardInput kDownButton{ KeyBoardButton::KB_DOWN, InputType::wasReleasedThisFrame };
	std::unique_ptr<ListNavCommand> kDownC{ std::make_unique<ListNavCommand>(listPtr, false) };
	KeyBoardInput kDownButton2{ KeyBoardButton::KB_S, InputType::wasReleasedThisFrame };
	std::unique_ptr<ListNavCommand> kDownC2{ std::make_unique<ListNavCommand>(listPtr, false) };
	input.AddKeyboardMouseBind(kDownButton, std::move(kDownC));
	input.AddKeyboardMouseBind(kDownButton2, std::move(kDownC2));

	scene.Add(std::move(startMenuTitle));
	scene.Add(std::move(listSelectionUI));
}

inline static void LoadInfoMenu(Scene& scene)
{
	const auto infoMenuTexture{ ResourceManager::Get().LoadTexture("Textures/UI/InfoMenu.png") };

	std::unique_ptr<GameObject> infoMenu{ std::make_unique<GameObject>() };

	auto infoTextureRenderer{ std::make_unique<TextureRenderer>(infoMenu.get(), infoMenuTexture) };
	auto infoMenuLogic{ std::make_unique<InfoMenu>(infoMenu.get()) };

	infoMenu->AddComponent(std::move(infoTextureRenderer));
	infoMenu->AddComponent(std::move(infoMenuLogic));

	scene.Add(std::move(infoMenu));
}

inline static void LoadEndMenu(Scene&)
{
	std::cout << "Loading Game Over Scene\n";
}

inline static void LoadTestLevel(Scene& scene)
{
	const glm::ivec2& windowSize{ GameManager::Get().GetWindowSize() };

	std::shared_ptr<Texture2D> playerSpriteSheet{ ResourceManager::Get().LoadTexture("Textures/PlayerSpriteSheet.png") };

	std::unique_ptr<GameObject> parentGameObj{};
	parentGameObj->SetWorldPosition(glm::vec2{ static_cast<float>(windowSize.x), 0.f });
	auto parentRenderObj{ std::make_unique<TextureRenderer>(parentGameObj.get(), playerSpriteSheet) };

	scene.Add(std::move(parentGameObj));
}

inline static void AddScenes()
{
	SceneManager& sceneM{ SceneManager::Get() };
	sceneM.CreateScene("LevelOneScene", LoadLevelOne);
	sceneM.CreateScene("LevelTwoScene", LoadLevelTwo);
	sceneM.CreateScene("LevelThreeScene", LoadLevelThree);
	sceneM.CreateScene("StartMenuScene", LoadStartMenu);
	sceneM.CreateScene("InfoMenuScene", LoadInfoMenu);
	sceneM.CreateScene("EndMenuScene", LoadEndMenu);

	sceneM.SetCurrentSceneByName("StartMenuScene");
}

// Main //
int main(int, char*[])
{
	const glm::ivec2& windowSize{ GameManager::Get().GetWindowSize() };

	MoE::Engine engine("../Resources/", windowSize.x, windowSize.y);

	engine.SetGameTitle("BurgerTimeTM_Clone");

	AddScenes();

#if defined DEBUG || defined _DEBUG
	engine.SetShowCursor(true);
#else
	engine.SetShowCursor(false);
#endif

	engine.Run();

    return 0;
}