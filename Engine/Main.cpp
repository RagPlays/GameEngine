
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <memory>
#include "Engine.h"
#include "Timer.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FpsComponent.h"
#include "RotateAroundParentComponent.h"

#include "PlayerComponent.h"
#include "PlayerStatsComponent.h"

#include "PlayerMoveCommand.h"
#include "PlayerKillCommand.h"
#include "PlayerPickupCommand.h"


void load(int width, int height)
{
	// Get References
	Scene& scene{ SceneManager::Get().CreateScene("Prog4EngineCreation") };
	Timer& timer{ Timer::Get() };
	InputManager& input{ InputManager::Get() };

	// Basics
	timer.EnableVSync();

	// Loading in
	std::shared_ptr<Font> font{ ResourceManager::Get().LoadFont("Lingua.otf", 20) };
	std::shared_ptr<Font> smallFont{ ResourceManager::Get().LoadFont("Lingua.otf", 15) };
	std::shared_ptr<Texture2D> backgroundTexture{ ResourceManager::Get().LoadTexture("background.tga") };
	std::shared_ptr<Texture2D> burgerTimeFigure{ ResourceManager::Get().LoadTexture("burgerTimePlayer.png") };

	// background
	std::unique_ptr<GameObject> background{ std::make_unique<GameObject>() };
	background->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(background.get(), backgroundTexture));
	background->GetComponent<RenderComponent>()->SetTextureDimentions({ width, height });

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
	std::unique_ptr<PlayerMoveCommand> kPlayerUp{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::vec3{0.f, -1.f, 0.f}) };
	// Left
	KeyBoardInput kGoLeftInput{ SDL_SCANCODE_A, InputType::ispressed };
	std::unique_ptr<PlayerMoveCommand> kPlayerLeft{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::vec3{-1.f, 0.f, 0.f}) };
	// Down
	KeyBoardInput kGoDownInput{ SDL_SCANCODE_S, InputType::ispressed };
	std::unique_ptr<PlayerMoveCommand> kPlayerDown{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::vec3{0.f, 1.f, 0.f}) };
	// Right
	KeyBoardInput kGoRightInput{ SDL_SCANCODE_D, InputType::ispressed };
	std::unique_ptr<PlayerMoveCommand> kPlayerRight{ std::make_unique<PlayerMoveCommand>(kInputPlayerComp, glm::vec3{1.f, 0.f, 0.f}) };
	// Kill
	KeyBoardInput kKillInput{ SDL_SCANCODE_C, InputType::wasPressedThisFrame };
	std::unique_ptr<PlayerKillCommand> kPlayerKill{ std::make_unique<PlayerKillCommand>(kInputPlayerComp) };
	// Pickups
	KeyBoardInput kPickupInput{ SDL_SCANCODE_Z, InputType::wasPressedThisFrame }; // 10 points
	KeyBoardInput kLargePickupInput{ SDL_SCANCODE_X, InputType::wasPressedThisFrame }; // 100 points
	std::unique_ptr<PlayerPickupCommand> kPlayerPickup{ std::make_unique<PlayerPickupCommand>(kInputPlayerComp, 10) };
	std::unique_ptr<PlayerPickupCommand> kPlayerPickupLarge{ std::make_unique<PlayerPickupCommand>(kInputPlayerComp, 100) };

	// Add Binds
	input.AddKeyboardMouseBind(kGoUpInput, std::move(kPlayerUp));
	input.AddKeyboardMouseBind(kGoLeftInput, std::move(kPlayerLeft));
	input.AddKeyboardMouseBind(kGoDownInput, std::move(kPlayerDown));
	input.AddKeyboardMouseBind(kGoRightInput, std::move(kPlayerRight));
	input.AddKeyboardMouseBind(kKillInput, std::move(kPlayerKill));
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
	std::unique_ptr<PlayerMoveCommand> cPlayerUp{ std::make_unique<PlayerMoveCommand>(cInputPlayerComp, glm::vec3{0.f, -1.f, 0.f}) };
	// Left
	ControllerInput cGoLeftInput{ SDL_CONTROLLER_BUTTON_DPAD_LEFT, InputType::ispressed };
	std::unique_ptr<PlayerMoveCommand> cPlayerLeft{ std::make_unique<PlayerMoveCommand>(cInputPlayerComp, glm::vec3{-1.f, 0.f, 0.f}) };
	// Down
	ControllerInput cGoDownInput{ SDL_CONTROLLER_BUTTON_DPAD_DOWN, InputType::ispressed };
	std::unique_ptr<PlayerMoveCommand> cPlayerDown{ std::make_unique<PlayerMoveCommand>(cInputPlayerComp, glm::vec3{0.f, 1.f, 0.f}) };
	// Right
	ControllerInput cGoRightInput{ SDL_CONTROLLER_BUTTON_DPAD_RIGHT, InputType::ispressed };
	std::unique_ptr<PlayerMoveCommand> cPlayerRight{ std::make_unique<PlayerMoveCommand>(cInputPlayerComp, glm::vec3{1.f, 0.f, 0.f}) };
	// Kill
	ControllerInput cKillInput{ SDL_CONTROLLER_BUTTON_X, InputType::wasPressedThisFrame };
	std::unique_ptr<PlayerKillCommand> cPlayerKill{ std::make_unique<PlayerKillCommand>(cInputPlayerComp) };
	// Pickups
	ControllerInput cPickupInput{ SDL_CONTROLLER_BUTTON_A, InputType::wasPressedThisFrame }; // 10 points
	ControllerInput cLargePickupInput{ SDL_CONTROLLER_BUTTON_B, InputType::wasPressedThisFrame }; // 100 points
	std::unique_ptr<PlayerPickupCommand> cPlayerPickup{ std::make_unique<PlayerPickupCommand>(cInputPlayerComp, 10) };
	std::unique_ptr<PlayerPickupCommand> cPlayerPickupLarge{ std::make_unique<PlayerPickupCommand>(cInputPlayerComp, 100) };

	// Add Binds
	input.AddControllerBind(cGoUpInput, std::move(cPlayerUp), controllerOne->GetControllerIdx());
	input.AddControllerBind(cGoLeftInput, std::move(cPlayerLeft), controllerOne->GetControllerIdx());
	input.AddControllerBind(cGoDownInput, std::move(cPlayerDown), controllerOne->GetControllerIdx());
	input.AddControllerBind(cGoRightInput, std::move(cPlayerRight), controllerOne->GetControllerIdx());
	input.AddControllerBind(cKillInput, std::move(cPlayerKill), controllerOne->GetControllerIdx());
	input.AddControllerBind(cPickupInput, std::move(cPlayerPickup), controllerOne->GetControllerIdx());
	input.AddControllerBind(cLargePickupInput, std::move(cPlayerPickupLarge), controllerOne->GetControllerIdx());

	// Controller Player 2 //
	// GameObject with components
	std::unique_ptr<GameObject> controllerPlayer2{ std::make_unique<GameObject>() };
	controllerPlayer2->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(controllerPlayer2.get(), burgerTimeFigure));
	controllerPlayer2->AddComponent<PlayerComponent>(std::make_unique<PlayerComponent>(controllerPlayer2.get(), 200.f));
	controllerPlayer2->SetWorldPosition({ width / 2.f + 40.f, height / 2.f, 0.f });

	PlayerComponent* cInputPlayerComp2{ controllerPlayer2->GetComponent<PlayerComponent>() };
	// Input
	const int controllerIdxTwo{ 1 };
	input.AddController(controllerIdxTwo);
	const Controller* controllerTwo{ input.GetController(controllerIdxTwo) };
	// Up
	std::unique_ptr<PlayerMoveCommand> c2PlayerUp{ std::make_unique<PlayerMoveCommand>(cInputPlayerComp2, glm::vec3{0.f, -1.f, 0.f}) };
	// Left
	std::unique_ptr<PlayerMoveCommand> c2PlayerLeft{ std::make_unique<PlayerMoveCommand>(cInputPlayerComp2, glm::vec3{-1.f, 0.f, 0.f}) };
	// Down
	std::unique_ptr<PlayerMoveCommand> c2PlayerDown{ std::make_unique<PlayerMoveCommand>(cInputPlayerComp2, glm::vec3{0.f, 1.f, 0.f}) };
	// Right
	std::unique_ptr<PlayerMoveCommand> c2PlayerRight{ std::make_unique<PlayerMoveCommand>(cInputPlayerComp2, glm::vec3{1.f, 0.f, 0.f}) };

	// Add Binds
	input.AddControllerBind(cGoUpInput, std::move(c2PlayerUp), controllerTwo->GetControllerIdx());
	input.AddControllerBind(cGoLeftInput, std::move(c2PlayerLeft), controllerTwo->GetControllerIdx());
	input.AddControllerBind(cGoDownInput, std::move(c2PlayerDown), controllerTwo->GetControllerIdx());
	input.AddControllerBind(cGoRightInput, std::move(c2PlayerRight), controllerTwo->GetControllerIdx());

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
	keyboardPlayerStats->AddComponent<PlayerStatsComponent>(std::make_unique<PlayerStatsComponent>(keyboardPlayerStats.get(), kInputPlayerComp));
	keyboardPlayerStats->SetWorldPosition({ 0.f, height / 2.f, 0.f });

	std::unique_ptr<GameObject> controllerPlayerStats1{ std::make_unique<GameObject>() };
	controllerPlayerStats1->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(controllerPlayerStats1.get()));
	controllerPlayerStats1->AddComponent<TextComponent>(std::make_unique<TextComponent>(controllerPlayerStats1.get(), smallFont));
	controllerPlayerStats1->AddComponent<PlayerStatsComponent>(std::make_unique<PlayerStatsComponent>(controllerPlayerStats1.get(), cInputPlayerComp));
	controllerPlayerStats1->SetWorldPosition({ 0.f, height / 2.f + 40.f, 0.f });

	std::unique_ptr<GameObject> controllerPlayerStats2{ std::make_unique<GameObject>() };
	controllerPlayerStats2->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(controllerPlayerStats2.get()));
	controllerPlayerStats2->AddComponent<TextComponent>(std::make_unique<TextComponent>(controllerPlayerStats2.get(), smallFont));
	controllerPlayerStats2->AddComponent<PlayerStatsComponent>(std::make_unique<PlayerStatsComponent>(controllerPlayerStats2.get(), cInputPlayerComp2));
	controllerPlayerStats2->SetWorldPosition({ 0.f, height / 2.f + 80.f, 0.f });


	// Add To Scene //
	scene.Add(std::move(background));
	scene.Add(std::move(logo));
	scene.Add(std::move(fpsDisplay));

	scene.Add(std::move(pcPlayer));
	scene.Add(std::move(controllerPlayer));
	scene.Add(std::move(controllerPlayer2));

	scene.Add(std::move(keyboardInputInfo));
	scene.Add(std::move(controllerInputInfo));

	scene.Add(std::move(keyboardPlayerStats));
	scene.Add(std::move(controllerPlayerStats1));
	scene.Add(std::move(controllerPlayerStats2));
}

int main(int, char*[]) 
{
	constexpr int windowWidth{ 1280 };
	constexpr int windowHeight{ 720 };

	Engine engine("../Resources/", "Prog4 Engine", windowWidth, windowHeight);
	load(windowWidth, windowHeight);
	engine.Run();
    return 0;
}