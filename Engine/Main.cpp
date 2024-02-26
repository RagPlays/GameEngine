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
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FpsComponent.h"
#include "Texture2D.h"

void load()
{
	Scene& scene{ SceneManager::GetInstance().CreateScene("Demo") };

	// Loading in
	std::shared_ptr<Font> font{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 15) };
	std::shared_ptr<Texture2D> backgroundTexture{ ResourceManager::GetInstance().LoadTexture("background.tga") };

	// background
	std::shared_ptr<GameObject> background{ std::make_shared<GameObject>() };
	std::shared_ptr<TextureComponent> backgroundTextureComponent{ std::make_shared<TextureComponent>(background.get(), backgroundTexture) };
	background->AddComponent(backgroundTextureComponent);
	scene.Add(background);

	// logo
	std::shared_ptr<GameObject> logo{ std::make_shared<GameObject>() };
	std::shared_ptr<TextureComponent> logoTextureComponent{ std::make_shared<TextureComponent>(logo.get(), "logo.tga") };
	logo->AddComponent(logoTextureComponent);
	logo->SetPosition(216.f, 180.f);
	scene.Add(logo);

	// text
	std::shared_ptr<GameObject> daeText{ std::make_shared<GameObject>() };
	std::shared_ptr<TextComponent> textComponent{ std::make_shared<TextComponent>(daeText.get(), "Programming 4 Assignment", font) };
	daeText->SetPosition(80.f, 20.f);
	daeText->AddComponent(textComponent);
	scene.Add(daeText);

	// FPS
	std::shared_ptr<GameObject> fpsDisplay{ std::make_shared<GameObject>() };
	std::shared_ptr< FpsComponent> fpsComponent{ std::make_shared<FpsComponent>(fpsDisplay.get(), font) };
	fpsDisplay->AddComponent(fpsComponent);
	fpsDisplay->SetPosition(20.f, 20.f);
	scene.Add(fpsDisplay);
}

int main(int, char*[]) 
{
	Engine engine("../Resources/", "Prog4 Engine", 640, 480);
	engine.Run(load);
    return 0;
}