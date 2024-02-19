#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Engine.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"

void load()
{
	Scene& scene{ SceneManager::GetInstance().CreateScene("Demo") };

	std::shared_ptr<GameObject> gameObj{ std::make_shared<GameObject>() };
	gameObj->SetTexture("background.tga");
	scene.Add(gameObj);

	gameObj = std::make_shared<GameObject>();
	gameObj->SetTexture("logo.tga");
	gameObj->SetPosition(216, 180);
	scene.Add(gameObj);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);
}

int main(int, char*[]) 
{
	Engine engine("../Resources/");
	engine.Run(load);
    return 0;
}