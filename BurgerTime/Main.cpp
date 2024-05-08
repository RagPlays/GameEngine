#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>
#include <memory>

#include "Engine.h"

#include "ServiceLocator.h"
#include "Timer.h"
#include "SceneManager.h"
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

void LoadTestScene(Engine* engine, int width, int height)
{
	engine->SetGameTitle("TestScene");
	// Get References
	Scene& scene{ SceneManager::Get().CreateScene("TestScene") };
	Timer& timer{ Timer::Get() };
	EventQueue& eventQueue{ EventQueue::Get() };
	InputManager& input{ InputManager::Get() };
	SoundSystem& soundSystem{ ServiceLocator::GetSoundSystem() };

	// Basics
	//timer.EnableVSync();
	timer.DisableVSync();
	//timer.EnableFpsCap(165);

	// EventQueue
	eventQueue.AddHandler(std::make_unique<SoundEventHandler>());

	// Loading in
	const ResourceManager& resourceManager{ ResourceManager::Get() };
	std::shared_ptr<Font> font{ resourceManager.LoadFont("Lingua.otf", 20) };
	std::shared_ptr<Font> smallFont{ resourceManager.LoadFont("Lingua.otf", 15) };

	std::shared_ptr<Texture2D> backgroundTexture{ resourceManager.LoadTexture("background.tga") };
	std::shared_ptr<Texture2D> burgerTimeFigure{ resourceManager.LoadTexture("burgerTimePlayer.png") };
	std::shared_ptr<Texture2D> DAELogo{ resourceManager.LoadTexture("logo.tga") };

	// background
	std::unique_ptr<GameObject> background{ std::make_unique<GameObject>() };
	background->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(background.get(), backgroundTexture));
	background->GetComponent<RenderComponent>()->SetTextureDimensions({ width, height });

	// logo
	std::unique_ptr<GameObject> logo{ std::make_unique<GameObject>() };
	logo->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(logo.get(), DAELogo));
	const int logoWidth{ logo->GetComponent<RenderComponent>()->GetTextureWidth() };
	logo->SetLocalPosition({ (width / 2.f) - (logoWidth / 2.f), (height / 3.f) });

	// FPS
	std::unique_ptr<GameObject> fpsDisplay{ std::make_unique<GameObject>() };
	fpsDisplay->AddComponent<FpsComponent>(std::make_unique<FpsComponent>(fpsDisplay.get()));
	fpsDisplay->AddComponent<TextComponent>(std::make_unique<TextComponent>(fpsDisplay.get(), font));
	fpsDisplay->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(fpsDisplay.get()));
	fpsDisplay->SetLocalPosition({ 20.f, 20.f });

	// WASD Player //
	// GameObject with components
	std::unique_ptr<GameObject> pcPlayer{ std::make_unique<GameObject>() };
	pcPlayer->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(pcPlayer.get(), burgerTimeFigure));
	pcPlayer->AddComponent<PlayerComponent>(std::make_unique<PlayerComponent>(pcPlayer.get()));
	pcPlayer->AddComponent<PlayerMovementComponent>(std::make_unique<PlayerMovementComponent>(pcPlayer.get(), 100.f));
	pcPlayer->SetWorldPosition({ width / 2.f - 40.f, height / 2.f });

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

	// Pickups
	KeyBoardInput kPickupInput{ SDL_SCANCODE_Z, InputType::wasReleasedThisFrame };
	KeyBoardInput kLargePickupInput{ SDL_SCANCODE_X, InputType::wasReleasedThisFrame };

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

	// Controller Player 1 //
	// GameObject with components
	std::unique_ptr<GameObject> controllerPlayer{ std::make_unique<GameObject>() };
	controllerPlayer->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(controllerPlayer.get(), burgerTimeFigure));
	controllerPlayer->AddComponent<PlayerComponent>(std::make_unique<PlayerComponent>(controllerPlayer.get()));
	controllerPlayer->AddComponent<PlayerMovementComponent>(std::make_unique<PlayerMovementComponent>(controllerPlayer.get(), 100.f));
	controllerPlayer->SetWorldPosition({ width / 2.f, height / 2.f });

	PlayerMovementComponent* cInputPlayerComp{ controllerPlayer->GetComponent<PlayerMovementComponent>() };
	// Input
	const int controllerIdxOne{ 0 };
	input.AddController(controllerIdxOne);
	const Controller* controllerOne{ input.GetController(controllerIdxOne) };
	// Up
	ControllerInput cGoUpInput{ SDL_CONTROLLER_BUTTON_DPAD_UP, InputType::ispressed };
	ControllerInput cStopUpInput{ SDL_CONTROLLER_BUTTON_DPAD_UP, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> cPlayerUp{ std::make_unique<PlayerMoveCommand>(cInputPlayerComp, glm::ivec2{0, -1}) };
	std::unique_ptr<PlayerStopCommand> cPlayerStopUp{ std::make_unique<PlayerStopCommand>(cInputPlayerComp, glm::ivec2{0, -1}) };
	// Left
	ControllerInput cGoLeftInput{ SDL_CONTROLLER_BUTTON_DPAD_LEFT, InputType::ispressed };
	ControllerInput cStopLeftInput{ SDL_CONTROLLER_BUTTON_DPAD_LEFT, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> cPlayerLeft{ std::make_unique<PlayerMoveCommand>(cInputPlayerComp, glm::ivec2{-1, 0}) };
	std::unique_ptr<PlayerStopCommand> cPlayerStopLeft{ std::make_unique<PlayerStopCommand>(cInputPlayerComp, glm::ivec2{-1, 0}) };
	// Down
	ControllerInput cGoDownInput{ SDL_CONTROLLER_BUTTON_DPAD_DOWN, InputType::ispressed };
	ControllerInput cStopDownInput{ SDL_CONTROLLER_BUTTON_DPAD_DOWN, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> cPlayerDown{ std::make_unique<PlayerMoveCommand>(cInputPlayerComp, glm::ivec2{0, 1}) };
	std::unique_ptr<PlayerStopCommand> cPlayerStopDown{ std::make_unique<PlayerStopCommand>(cInputPlayerComp, glm::ivec2{0, 1}) };
	// Right
	ControllerInput cGoRightInput{ SDL_CONTROLLER_BUTTON_DPAD_RIGHT, InputType::ispressed };
	ControllerInput cStopRightInput{ SDL_CONTROLLER_BUTTON_DPAD_RIGHT, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerMoveCommand> cPlayerRight{ std::make_unique<PlayerMoveCommand>(cInputPlayerComp, glm::ivec2{1, 0}) };
	std::unique_ptr<PlayerStopCommand> cPlayerStopRight{ std::make_unique<PlayerStopCommand>(cInputPlayerComp, glm::ivec2{1, 0}) };
	
	// Pickups
	ControllerInput cPickupInput{ SDL_CONTROLLER_BUTTON_A, InputType::wasReleasedThisFrame };
	ControllerInput cLargePickupInput{ SDL_CONTROLLER_BUTTON_B, InputType::wasReleasedThisFrame };

	// Add Binds
	// Up
	input.AddControllerBind(cGoUpInput, std::move(cPlayerUp), controllerOne->GetControllerIdx());
	input.AddControllerBind(cStopUpInput, std::move(cPlayerStopUp), controllerOne->GetControllerIdx());
	// Left
	input.AddControllerBind(cGoLeftInput, std::move(cPlayerLeft), controllerOne->GetControllerIdx());
	input.AddControllerBind(cStopLeftInput, std::move(cPlayerStopLeft), controllerOne->GetControllerIdx());
	// Down
	input.AddControllerBind(cGoDownInput, std::move(cPlayerDown), controllerOne->GetControllerIdx());
	input.AddControllerBind(cStopDownInput, std::move(cPlayerStopDown), controllerOne->GetControllerIdx());
	// Right
	input.AddControllerBind(cGoRightInput, std::move(cPlayerRight), controllerOne->GetControllerIdx());
	input.AddControllerBind(cStopRightInput, std::move(cPlayerStopRight), controllerOne->GetControllerIdx());

	// PlayerStats //

	PlayerComponent* pcPlayerComp{ pcPlayer->GetComponent<PlayerComponent>() };
	PlayerComponent* controllerPlayerComp{ controllerPlayer->GetComponent<PlayerComponent>() };
	// Stats
	std::unique_ptr<GameObject> keyboardPlayerStats{ std::make_unique<GameObject>() };
	keyboardPlayerStats->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(keyboardPlayerStats.get()));
	keyboardPlayerStats->AddComponent<TextComponent>(std::make_unique<TextComponent>(keyboardPlayerStats.get(), smallFont));
	keyboardPlayerStats->AddComponent<PlayerStatsComponent>(std::make_unique<PlayerStatsComponent>(keyboardPlayerStats.get()));
	keyboardPlayerStats->SetWorldPosition({ 0.f, height / 2.f });
	pcPlayerComp->RegisterObserver(keyboardPlayerStats->GetComponent<PlayerStatsComponent>());

	std::unique_ptr<GameObject> controllerPlayerStats{ std::make_unique<GameObject>() };
	controllerPlayerStats->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(controllerPlayerStats.get()));
	controllerPlayerStats->AddComponent<TextComponent>(std::make_unique<TextComponent>(controllerPlayerStats.get(), smallFont));
	controllerPlayerStats->AddComponent<PlayerStatsComponent>(std::make_unique<PlayerStatsComponent>(controllerPlayerStats.get()));
	controllerPlayerStats->SetWorldPosition({ 0.f, height / 2.f + 40.f });
	controllerPlayerComp->RegisterObserver(controllerPlayerStats->GetComponent<PlayerStatsComponent>());

	// SOUNDS //
	// Music
	soundSystem.AddSong("Sound/Music/forestMusic.mp3", MusicSoundID::calmMusic);
	// SoundEffects
	soundSystem.AddSoundEffect("Sound/SoundEffects/dieSF.wav", SoundEffectSoundID::die);


	// Add To Scene //
	scene.Add(std::move(background));
	scene.Add(std::move(logo));
	scene.Add(std::move(fpsDisplay));

	scene.Add(std::move(pcPlayer));
	scene.Add(std::move(controllerPlayer));

	scene.Add(std::move(keyboardPlayerStats));
	scene.Add(std::move(controllerPlayerStats));
}

void LoadGameScene(Engine* engine, int, int)
{
	// Set Title
	engine->SetGameTitle("Burger Time");

	// References
	Scene& scene{ SceneManager::Get().CreateScene("GameScene") };
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
	pcPlayer->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(pcPlayer.get(), playerSpriteSheet));
	pcPlayer->AddComponent<PlayerComponent>(std::make_unique<PlayerComponent>(pcPlayer.get()));
	pcPlayer->AddComponent<PlayerMovementComponent>(std::make_unique<PlayerMovementComponent>(pcPlayer.get(), 100.f));

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

void LoadEmptyScene()
{
	SceneManager::Get().CreateScene("EmptyScene");
}

void Load(Engine* engine, int width, int height)
{
	//LoadEmptyScene();
	LoadGameScene(engine, width, height);
	//LoadTestScene(engine, width, height);

	//SceneManager::Get().SetCurrentSceneByName("TestScene");

	/*engine = nullptr;
	width = 0;
	height = 0;*/
}

int main(int, char*[]) 
{
	constexpr int windowWidth{ 240 * 3 }; // Game scaling 3 from original
	constexpr int windowHeight{ 240 * 3 };

	Engine engine("../Resources/", windowWidth, windowHeight);
	Load(&engine, windowWidth, windowHeight);

	engine.Run();
    return 0;
}