
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
#include "PlayerMoveCommand.h"

void load(int width, int height)
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
	pcPlayer->AddComponent<PlayerComponent>(std::make_unique<PlayerComponent>(pcPlayer.get(), 100.f));
	pcPlayer->SetWorldPosition({ width / 2.f - 20.f, height / 2.f, 0.f });

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
	controllerPlayer->AddComponent<PlayerComponent>(std::make_unique<PlayerComponent>(controllerPlayer.get(), 200.f));
	controllerPlayer->SetWorldPosition({ width / 2.f + 20.f, height / 2.f, 0.f });

	PlayerComponent* cInputPlayerComp{ controllerPlayer->GetComponent<PlayerComponent>() };
	//// XinputInput
	//// Up
	//XinputControllerInput cGoUpInput{ XINPUT_GAMEPAD_DPAD_UP, InputType::ispressed };
	//std::unique_ptr<PlayerMoveCommand> cPlayerUp{ std::make_unique<PlayerMoveCommand>(cInputPlayerComp, glm::vec3{0.f, -1.f, 0.f}) };
	//// Left
	//XinputControllerInput cGoLeftInput{ XINPUT_GAMEPAD_DPAD_LEFT, InputType::ispressed };
	//std::unique_ptr<PlayerMoveCommand> cPlayerLeft{ std::make_unique<PlayerMoveCommand>(cInputPlayerComp, glm::vec3{-1.f, 0.f, 0.f}) };
	//// Down
	//XinputControllerInput cGoDownInput{ XINPUT_GAMEPAD_DPAD_DOWN, InputType::ispressed };
	//std::unique_ptr<PlayerMoveCommand> cPlayerDown{ std::make_unique<PlayerMoveCommand>(cInputPlayerComp, glm::vec3{0.f, 1.f, 0.f}) };
	//// Right
	//XinputControllerInput cGoRightInput{ XINPUT_GAMEPAD_DPAD_RIGHT, InputType::ispressed };
	//std::unique_ptr<PlayerMoveCommand> cPlayerRight{ std::make_unique<PlayerMoveCommand>(cInputPlayerComp, glm::vec3{1.f, 0.f, 0.f}) };

	//// Add Binds
	//input.AddXinputControllerBind(cGoUpInput, std::move(cPlayerUp));
	//input.AddXinputControllerBind(cGoLeftInput, std::move(cPlayerLeft));
	//input.AddXinputControllerBind(cGoDownInput, std::move(cPlayerDown));
	//input.AddXinputControllerBind(cGoRightInput, std::move(cPlayerRight));

	// Input
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

	// Add Binds
	input.AddControllerBind(cGoUpInput, std::move(cPlayerUp));
	input.AddControllerBind(cGoLeftInput, std::move(cPlayerLeft));
	input.AddControllerBind(cGoDownInput, std::move(cPlayerDown));
	input.AddControllerBind(cGoRightInput, std::move(cPlayerRight));

	// Add to scene
	scene.Add(std::move(controllerPlayer));
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