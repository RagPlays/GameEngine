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

#include "PlayerMoveCommand.h"
#include "PlayerStopCommand.h"
#include "PlayerKillCommand.h"
#include "PlayerPickupCommand.h"

#include "SoundEventHandler.h"

#include "SoundSystem.h"
#include "SoundIDStorage.h"

void LoadTestScene(int width, int height)
{
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
	eventQueue.SetHandler(std::make_unique<SoundEventHandler>());

	// Loading in
	std::shared_ptr<Font> font{ ResourceManager::Get().LoadFont("Lingua.otf", 20) };
	std::shared_ptr<Font> smallFont{ ResourceManager::Get().LoadFont("Lingua.otf", 15) };
	std::shared_ptr<Texture2D> backgroundTexture{ ResourceManager::Get().LoadTexture("background.tga") };
	std::shared_ptr<Texture2D> burgerTimeFigure{ ResourceManager::Get().LoadTexture("burgerTimePlayer.png") };

	// background
	std::unique_ptr<GameObject> background{ std::make_unique<GameObject>() };
	background->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(background.get(), backgroundTexture));
	background->GetComponent<RenderComponent>()->SetTextureDimensions({ width, height });

	// logo
	std::unique_ptr<GameObject> logo{ std::make_unique<GameObject>() };
	logo->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(logo.get(), "logo.tga"));
	int logoWidth{ logo->GetComponent<RenderComponent>()->GetTextureWidth() };
	logo->SetLocalPosition({ (width / 2.f) - (logoWidth / 2.f), (height / 3.f) , 0.f });

	// FPS
	std::unique_ptr<GameObject> fpsDisplay{ std::make_unique<GameObject>() };
	fpsDisplay->AddComponent<FpsComponent>(std::make_unique<FpsComponent>(fpsDisplay.get()));
	fpsDisplay->AddComponent<TextComponent>(std::make_unique<TextComponent>(fpsDisplay.get(), font));
	fpsDisplay->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(fpsDisplay.get()));
	fpsDisplay->SetLocalPosition({ 20.f, 20.f, 0.f });

	// WASD Player //
	// GameObject with components
	std::unique_ptr<GameObject> pcPlayer{ std::make_unique<GameObject>() };
	pcPlayer->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(pcPlayer.get(), burgerTimeFigure));
	pcPlayer->AddComponent<PlayerComponent>(std::make_unique<PlayerComponent>(pcPlayer.get(), 100.f));
	pcPlayer->SetWorldPosition({ width / 2.f - 40.f, height / 2.f, 0.f });

	PlayerComponent* kInputPlayerComp{ pcPlayer->GetComponent<PlayerComponent>() };
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

	// Kill
	KeyBoardInput kKillInput{ SDL_SCANCODE_C, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerKillCommand> kPlayerKill{ std::make_unique<PlayerKillCommand>(kInputPlayerComp) };
	// Pickups
	KeyBoardInput kPickupInput{ SDL_SCANCODE_Z, InputType::wasReleasedThisFrame };
	KeyBoardInput kLargePickupInput{ SDL_SCANCODE_X, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerPickupCommand> kPlayerPickup{ std::make_unique<PlayerPickupCommand>(kInputPlayerComp, PickupItem::smallItem) };
	std::unique_ptr<PlayerPickupCommand> kPlayerPickupLarge{ std::make_unique<PlayerPickupCommand>(kInputPlayerComp, PickupItem::bigItem) };

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
	// Kill
	input.AddKeyboardMouseBind(kKillInput, std::move(kPlayerKill));
	// Pickup
	input.AddKeyboardMouseBind(kPickupInput, std::move(kPlayerPickup));
	input.AddKeyboardMouseBind(kLargePickupInput, std::move(kPlayerPickupLarge));

	// Controller Player 1 //
	// GameObject with components
	std::unique_ptr<GameObject> controllerPlayer{ std::make_unique<GameObject>() };
	controllerPlayer->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(controllerPlayer.get(), burgerTimeFigure));
	controllerPlayer->AddComponent<PlayerComponent>(std::make_unique<PlayerComponent>(controllerPlayer.get(), 200.f));
	controllerPlayer->SetWorldPosition({ width / 2.f, height / 2.f, 0.f });

	PlayerComponent* cInputPlayerComp{ controllerPlayer->GetComponent<PlayerComponent>() };
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
	
	// Kill
	ControllerInput cKillInput{ SDL_CONTROLLER_BUTTON_X, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerKillCommand> cPlayerKill{ std::make_unique<PlayerKillCommand>(cInputPlayerComp) };
	// Pickups
	ControllerInput cPickupInput{ SDL_CONTROLLER_BUTTON_A, InputType::wasReleasedThisFrame };
	ControllerInput cLargePickupInput{ SDL_CONTROLLER_BUTTON_B, InputType::wasReleasedThisFrame };
	std::unique_ptr<PlayerPickupCommand> cPlayerPickup{ std::make_unique<PlayerPickupCommand>(cInputPlayerComp, PickupItem::smallItem) };
	std::unique_ptr<PlayerPickupCommand> cPlayerPickupLarge{ std::make_unique<PlayerPickupCommand>(cInputPlayerComp, PickupItem::bigItem) };

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
	// Kill
	input.AddControllerBind(cKillInput, std::move(cPlayerKill), controllerOne->GetControllerIdx());
	// Pickups
	input.AddControllerBind(cPickupInput, std::move(cPlayerPickup), controllerOne->GetControllerIdx());
	input.AddControllerBind(cLargePickupInput, std::move(cPlayerPickupLarge), controllerOne->GetControllerIdx());

	// PlayerStats //

	// Text
	std::unique_ptr<GameObject> keyboardInputInfo{ std::make_unique<GameObject>() };
	keyboardInputInfo->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(keyboardInputInfo.get()));
	keyboardInputInfo->AddComponent<TextComponent>(
		std::make_unique<TextComponent>(keyboardInputInfo.get(), smallFont, "Use WASD to move, C to inflict damage, Z and X to pick up."));
	keyboardInputInfo->SetLocalPosition({ 0.f, 100.f, 0.f });

	std::unique_ptr<GameObject> controllerInputInfo{ std::make_unique<GameObject>() };
	controllerInputInfo->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(controllerInputInfo.get()));
	controllerInputInfo->AddComponent<TextComponent>(
		std::make_unique<TextComponent>(controllerInputInfo.get(), smallFont, "Use the D-Pad to move, X to inflict damage, A and B to pick up."));
	controllerInputInfo->SetLocalPosition({ 0.f, 120.f, 0.f });

	// Stats
	std::unique_ptr<GameObject> keyboardPlayerStats{ std::make_unique<GameObject>() };
	keyboardPlayerStats->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(keyboardPlayerStats.get()));
	keyboardPlayerStats->AddComponent<TextComponent>(std::make_unique<TextComponent>(keyboardPlayerStats.get(), smallFont));
	keyboardPlayerStats->AddComponent<PlayerStatsComponent>(std::make_unique<PlayerStatsComponent>(keyboardPlayerStats.get()));
	keyboardPlayerStats->SetWorldPosition({ 0.f, height / 2.f, 0.f });
	kInputPlayerComp->RegisterObserver(keyboardPlayerStats->GetComponent<PlayerStatsComponent>());

	std::unique_ptr<GameObject> controllerPlayerStats{ std::make_unique<GameObject>() };
	controllerPlayerStats->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(controllerPlayerStats.get()));
	controllerPlayerStats->AddComponent<TextComponent>(std::make_unique<TextComponent>(controllerPlayerStats.get(), smallFont));
	controllerPlayerStats->AddComponent<PlayerStatsComponent>(std::make_unique<PlayerStatsComponent>(controllerPlayerStats.get()));
	controllerPlayerStats->SetWorldPosition({ 0.f, height / 2.f + 40.f, 0.f });
	cInputPlayerComp->RegisterObserver(controllerPlayerStats->GetComponent<PlayerStatsComponent>());


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

	scene.Add(std::move(keyboardInputInfo));
	scene.Add(std::move(controllerInputInfo));

	scene.Add(std::move(keyboardPlayerStats));
	scene.Add(std::move(controllerPlayerStats));
}

void LoadGameScene(int width, int height)
{
	Scene& scene{ SceneManager::Get().CreateScene("GameScene") };

	std::shared_ptr<Texture2D> backgroundTexture{ ResourceManager::Get().LoadTexture("background.tga") };

	// background
	std::unique_ptr<GameObject> background{ std::make_unique<GameObject>() };
	background->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(background.get(), backgroundTexture));
	background->GetComponent<RenderComponent>()->SetTextureDimensions({ width, height });

	scene.Add(std::move(background));
}

void Load(int width, int height)
{
	//LoadGameScene(width, height);
	LoadTestScene(width, height);

	SceneManager::Get().SetCurrentSceneByName("TestScene");
	//SceneManager::Get().SetCurrentSceneByName("GameScene");
}

int main(int, char*[]) 
{
	constexpr int windowWidth{ 1280 };
	constexpr int windowHeight{ 720 };

	Engine engine("../Resources/", windowWidth, windowHeight);
	Load(windowWidth, windowHeight);

	engine.Run();
    return 0;
}