
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

void load()
{
	Scene& scene{ SceneManager::GetInstance().CreateScene("Demo") };

	// Loading in
	std::shared_ptr<Font> font{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 20) };
	//std::shared_ptr<Texture2D> backgroundTexture{ ResourceManager::GetInstance().LoadTexture("background.tga") };
	std::shared_ptr<Texture2D> burgerTimeFigure{ ResourceManager::GetInstance().LoadTexture("burgerTimeSprites.png") };

	// background
	//std::shared_ptr<GameObject> background{ std::make_shared<GameObject>() };
	//background->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(background.get(), backgroundTexture));
	//scene.Add(background);

	//// logo
	//std::shared_ptr<GameObject> logo{ std::make_shared<GameObject>() };
	//logo->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(logo.get(), "logo.tga"));
	//logo->SetLocalPosition(216.f, 180.f);
	//scene.Add(logo);

	//// text
	//std::shared_ptr<GameObject> text{ std::make_shared<GameObject>() };
	//text->AddComponent<TextComponent>(std::make_shared<TextComponent>(text.get(), font, "Programming 4 Assignment"));
	//text->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(text.get()));
	//text->SetLocalPosition(185.f, 20.f);
	//scene.Add(text);

	// FPS
	/*std::shared_ptr<GameObject> fpsDisplay{ std::make_shared<GameObject>() };
	fpsDisplay->AddComponent<FpsComponent>(std::make_shared<FpsComponent>(fpsDisplay.get()));
	fpsDisplay->AddComponent<TextComponent>(std::make_shared<TextComponent>(fpsDisplay.get(), font));
	fpsDisplay->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(fpsDisplay.get()));
	fpsDisplay->SetLocalPosition(20.f, 20.f);
	scene.Add(fpsDisplay);*/

	// Burger Time Figure
	std::shared_ptr<GameObject> parentFigure{ std::make_shared<GameObject>() };
	parentFigure->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(parentFigure.get(), burgerTimeFigure));

	std::shared_ptr<GameObject> childFigure{ std::make_shared<GameObject>() };
	childFigure->AddComponent<RenderComponent>(std::make_shared<RenderComponent>(childFigure.get(), burgerTimeFigure));
	scene.Add(parentFigure);
	childFigure->SetParent(parentFigure);

	parentFigure->SetLocalPosition(200.f, 200.f);
	childFigure->SetLocalPosition(50.f, 50.f);
}

int main(int, char*[]) 
{
	Engine engine("../Resources/", "Prog4 Engine", 640, 480);
	engine.Run(load);
    return 0;
}