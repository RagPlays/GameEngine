#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>
#include <memory>

#include "Engine.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FpsComponent.h"
#include "Texture2D.h"

void load()
{
	Scene& scene{ SceneManager::GetInstance().CreateScene("Demo") };

	// Loading in
	std::shared_ptr<Font> font{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 20) };

	// background
	std::shared_ptr<GameObject> background{ std::make_shared<GameObject>() };
	background->AddComponent(std::make_shared<RenderComponent>(background.get(), ResourceManager::GetInstance().LoadTexture("background.tga")));
	scene.Add(background);

	// logo
	std::shared_ptr<GameObject> logo{ std::make_shared<GameObject>() };
	logo->AddComponent(std::make_shared<RenderComponent>(logo.get(), "logo.tga"));
	logo->SetPosition(216.f, 180.f);
	scene.Add(logo);

	// text
	std::shared_ptr<GameObject> text{ std::make_shared<GameObject>() };
	text->AddComponent(std::make_shared<TextComponent>(text.get(), font, "Programming 4 Assignment"));
	text->AddComponent(std::make_shared<RenderComponent>(text.get()));
	text->SetPosition(185.f, 20.f);
	scene.Add(text);

	// FPS
	std::shared_ptr<GameObject> fpsDisplay{ std::make_shared<GameObject>() };
	fpsDisplay->AddComponent(std::make_shared<FpsComponent>(fpsDisplay.get()));
	fpsDisplay->AddComponent(std::make_shared<TextComponent>(fpsDisplay.get(), font));
	fpsDisplay->AddComponent(std::make_shared<RenderComponent>(fpsDisplay.get()));
	fpsDisplay->SetPosition(20.f, 20.f);
	scene.Add(fpsDisplay);
}

int main(int, char*[]) 
{
	Engine engine("../Resources/", "Prog4 Engine", 640, 480);
	engine.Run(load);
    return 0;
}