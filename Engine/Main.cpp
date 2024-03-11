
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
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FpsComponent.h"
#include "RotateAroundParentComponent.h"

#include "ImGuiRenderer.h"
#include "ImGuiExercise1.h"
#include "ImGuiExercise2.h"

void load(int width, int height)
{
	// Get References
	Scene& scene{ SceneManager::Get().CreateScene("Prog4EngineCreation") };
	ImGuiRenderer& imGuiRenderer{ ImGuiRenderer::Get() };

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

	// ImGui //
	imGuiRenderer.AddImGuiComponent(std::make_unique<ImGuiExercise1>());
	imGuiRenderer.AddImGuiComponent(std::make_unique<ImGuiExercise2>());
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