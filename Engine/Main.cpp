
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

void load(int width, int height)
{
	Scene& scene{ SceneManager::Get().CreateScene("Prog4EngineCreation") };

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

	// Burger Time Figure
	std::unique_ptr<GameObject> burgerTime{ std::make_unique<GameObject>() };
	burgerTime->SetLocalPosition({ width / 2.f, height / 1.5f, 0.f });

	GameObject* parentFigure{ new GameObject{} };
	parentFigure->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(parentFigure, burgerTimeFigure));
	parentFigure->AddComponent<RotateAroundParentComponent>(std::make_unique<RotateAroundParentComponent>(parentFigure, 12.f));
	parentFigure->SetParent(burgerTime.get());

	GameObject* childFigure{ new GameObject{} };
	childFigure->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(childFigure, burgerTimeFigure));
	childFigure->AddComponent<RotateAroundParentComponent>(std::make_unique<RotateAroundParentComponent>(childFigure, 6.f));
	childFigure->SetParent(parentFigure);

	parentFigure->SetLocalPosition({ 10.f, 10.f, 0.f });
	childFigure->SetLocalPosition({ 30.f, 30.f, 0.f });

	scene.Add(std::move(burgerTime));

	// World relative position test
	std::unique_ptr<GameObject> testObj{ std::make_unique<GameObject>() };
	testObj->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(testObj.get(), burgerTimeFigure));
	testObj->SetWorldPosition({ width / 2.f, height / 2.f, 0.f });

	GameObject* testParentFigure{ new GameObject{} };
	testParentFigure->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(testParentFigure, burgerTimeFigure));
	testParentFigure->SetParent(testObj.get());

	GameObject* testParentFigure2{ new GameObject{} };
	testParentFigure2->AddComponent<RenderComponent>(std::make_unique<RenderComponent>(testParentFigure2, burgerTimeFigure));
	testParentFigure2->SetParent(testParentFigure);

	testParentFigure->SetLocalPosition({ 20.f, 10.f, 0.f });
	testParentFigure2->SetLocalPosition({ 20.f, 10.f, 0.f });

	testParentFigure->SetWorldPosition({ 100.f, 100.f, 0.f });
	testObj->SetWorldPosition({ 800.f, 500.f, 0.f });

	scene.Add(std::move(testObj));
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