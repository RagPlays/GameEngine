#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Engine.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "chrono"
#include "thread"

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

Engine::Engine(const std::string &dataPath, const std::string& title)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

Engine::~Engine()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void Engine::Run(const std::function<void()>& load)
{
	// Run Function
	load();

	// Get Instances
	Renderer& renderer = Renderer::GetInstance();
	SceneManager& sceneManager = SceneManager::GetInstance();
	InputManager& input = InputManager::GetInstance();

	// Create Variables
	std::chrono::duration<long> msPerFrame{ 33 };
	bool doContinue{ true };
	auto lastTime{ std::chrono::high_resolution_clock::now() };
	float lag{ 0.f };
	const float fixedTimeStep{ 0.02f };

	while (doContinue)
	{
		// DeltaTime
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const float elapsedSec = std::chrono::duration<float>(currentTime - lastTime).count();

		// Input
		doContinue = input.ProcessInput();

		// Fixed Update -> only for physics / networking
		while (lag >= fixedTimeStep)
		{
			sceneManager.FixedUpdate(fixedTimeStep);
			lag -= fixedTimeStep;
		}

		// Update
		sceneManager.Update(elapsedSec);

		// LateUpdate
		sceneManager.LateUpdate(elapsedSec);

		// Render
		renderer.Render();

		// Sleep -> FPS cap
		/*const std::chrono::nanoseconds sleepTime{ currentTime + std::chrono::milliseconds(msPerFrame) - std::chrono::high_resolution_clock::now() };
		std::this_thread::sleep_for(sleepTime);*/
	}
}
