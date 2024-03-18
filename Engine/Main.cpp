
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include <memory>
#include "Engine.h"
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

#include "ImGuiRenderer.h"
#include "ImGuiExercise1.h"
#include "ImGuiExercise2.h"

#include "PlayerLeftCommand.h"
#include "PlayerRightCommand.h"
#include "PlayerUpCommand.h"
#include "PlayerDownCommand.h"


void LoadScene(int width, int height)
{
	// Get References
	Scene& scene{ SceneManager::Get().CreateScene("Prog4EngineCreation") };
	InputManager& input{ InputManager::Get() };

	// Loading in
	std::shared_ptr<Font> font{ ResourceManager::Get().LoadFont("Lingua.otf", 20) };
	std::shared_ptr<Texture2D> backgroundTexture{ ResourceManager::Get().LoadTexture("background.tga") };
	std::shared_ptr<Texture2D> burgerTimeFigure{ ResourceManager::Get().LoadTexture("burgerTimePlayer.png") };

	// background
	std::unique_ptr<GameObject> background{ std::make_unique<GameObject>() };
	background->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(background.get(), backgroundTexture));
	background->GetComponent<RenderComponent>()->SetTextureDimentions({ width, height });
	scene.Add(std::move(background));

	// logo
	std::unique_ptr<GameObject> logo{ std::make_unique<GameObject>() };
	logo->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(logo.get(), "logo.tga"));
	int logoWidth{ logo->GetComponent<RenderComponent>()->GetTextureWidth() };
	logo->SetLocalPosition({ (width / 2.f) - (logoWidth / 2.f), (height / 3.f) , 0.f });
	scene.Add(std::move(logo));

	// FPS
	std::unique_ptr<GameObject> fpsDisplay{ std::make_unique<GameObject>() };
	fpsDisplay->AddComponent<FpsComponent>(std::make_unique<FpsComponent>(fpsDisplay.get()));
	fpsDisplay->AddComponent<TextComponent>(std::make_unique<TextComponent>(fpsDisplay.get(), font));
	fpsDisplay->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(fpsDisplay.get()));
	fpsDisplay->SetLocalPosition({ 20.f, 20.f, 0.f });
	scene.Add(std::move(fpsDisplay));

	// WASD Player //
	// GameObject with components
	std::unique_ptr<GameObject> pcPlayer{ std::make_unique<GameObject>() };
	pcPlayer->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(pcPlayer.get(), burgerTimeFigure));
	pcPlayer->AddComponent<PlayerComponent>(std::make_unique<PlayerComponent>(pcPlayer.get()));
	pcPlayer->SetWorldPosition({ width / 2.f - 20.f, height / 2.f, 0.f });

	PlayerComponent* kInputPlayerComp{ pcPlayer->GetComponent<PlayerComponent>() };
	// Input
	// Up
	KeyBoardInput kGoUpInput{ SDL_SCANCODE_W, InputType::ispressed };
	std::unique_ptr<PlayerUpCommand> kPlayerUp{ std::make_unique<PlayerUpCommand>(kInputPlayerComp) };
	// Left
	KeyBoardInput kGoLeftInput{ SDL_SCANCODE_A, InputType::ispressed };
	std::unique_ptr<PlayerLeftCommand> kPlayerLeft{ std::make_unique<PlayerLeftCommand>(kInputPlayerComp) };
	// Down
	KeyBoardInput kGoDownInput{ SDL_SCANCODE_S, InputType::ispressed };
	std::unique_ptr<PlayerDownCommand> kPlayerDown{ std::make_unique<PlayerDownCommand>(kInputPlayerComp) };
	// Right
	KeyBoardInput kGoRightInput{ SDL_SCANCODE_D, InputType::ispressed };
	std::unique_ptr<PlayerRightCommand> kPlayerRight{ std::make_unique<PlayerRightCommand>(kInputPlayerComp) };

	// Add Binds
	input.AddKeyboardMouseBind(kGoUpInput, std::move(kPlayerUp));
	input.AddKeyboardMouseBind(kGoLeftInput, std::move(kPlayerLeft));
	input.AddKeyboardMouseBind(kGoDownInput, std::move(kPlayerDown));
	input.AddKeyboardMouseBind(kGoRightInput, std::move(kPlayerRight));
	
	// Add to scene
	scene.Add(std::move(pcPlayer));

	// Controller Player //
	// GameObject with components
	std::unique_ptr<GameObject> controllerPlayer{ std::make_unique<GameObject>() };
	controllerPlayer->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(controllerPlayer.get(), burgerTimeFigure));
	controllerPlayer->AddComponent<PlayerComponent>(std::make_unique<PlayerComponent>(controllerPlayer.get()));
	controllerPlayer->SetWorldPosition({ width / 2.f + 20.f, height / 2.f, 0.f });

	PlayerComponent* cInputPlayerComp{ controllerPlayer->GetComponent<PlayerComponent>() };
	// Input
	// Up
	ControllerInput cGoUpInput{ XINPUT_GAMEPAD_DPAD_UP, InputType::ispressed };
	std::unique_ptr<PlayerUpCommand> cPlayerUp{ std::make_unique<PlayerUpCommand>(cInputPlayerComp) };
	// Left
	ControllerInput cGoLeftInput{ XINPUT_GAMEPAD_DPAD_LEFT, InputType::ispressed };
	std::unique_ptr<PlayerLeftCommand> cPlayerLeft{ std::make_unique<PlayerLeftCommand>(cInputPlayerComp) };
	// Down
	ControllerInput cGoDownInput{ XINPUT_GAMEPAD_DPAD_DOWN, InputType::ispressed };
	std::unique_ptr<PlayerDownCommand> cPlayerDown{ std::make_unique<PlayerDownCommand>(cInputPlayerComp) };
	// Right
	ControllerInput cGoRightInput{ XINPUT_GAMEPAD_DPAD_RIGHT, InputType::ispressed };
	std::unique_ptr<PlayerRightCommand> cPlayerRight{ std::make_unique<PlayerRightCommand>(cInputPlayerComp) };

	// Add Binds
	input.AddControllerBind(cGoUpInput, std::move(cPlayerUp));
	input.AddControllerBind(cGoLeftInput, std::move(cPlayerLeft));
	input.AddControllerBind(cGoDownInput, std::move(cPlayerDown));
	input.AddControllerBind(cGoRightInput, std::move(cPlayerRight));

	// Add to scene
	scene.Add(std::move(controllerPlayer));
}

void load(int width, int height)
{
	LoadScene(width, height);
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