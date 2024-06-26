#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <stdexcept>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Engine.h"

// Singletons
#include "InputManager.h"
#include "SceneManager.h"
#include "EventQueue.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "Timer.h"

#include "SDLSoundSystem.h"

namespace MoE
{
	Engine::Engine(const std::string& dataPath, unsigned int width, unsigned int height)
		: m_WindowWidth{ width }
		, m_WindowHeight{ height }
		, m_pWindow{}
	{
#if defined _DEBUG || DEBUG
		PrintSDLVersion();
#endif

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO))
		{
			throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
		}
		if (TTF_Init())
		{
			throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, SDL_GetNumAudioDevices(0), 2048))
		{
			throw std::runtime_error(std::string("Failed to load support for audio: ") + SDL_GetError());
		}

		m_pWindow = SDL_CreateWindow(
			"No_Title",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_WindowWidth,
			m_WindowHeight,
			SDL_WINDOW_OPENGL
		);

		if (!m_pWindow)
		{
			throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
		}

#if defined _DEBUG || defined DEBUG
		ServiceLocator::RegisterSoundSystem(std::make_unique<LoggingSoundSystem>(std::make_unique<SDLSoundSystem>()));
#else
		ServiceLocator::RegisterSoundSystem(std::make_unique<SDLSoundSystem>());
#endif

		Renderer::Get().Init(m_pWindow);
		ResourceManager::Get().Init(dataPath);
	}

	Engine::~Engine()
	{
		SceneManager::Get().Destroy();
		Renderer::Get().Destroy();
		SDL_DestroyWindow(m_pWindow);
		m_pWindow = nullptr;
		Mix_CloseAudio();
		Mix_Quit();
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	void Engine::Run()
	{
		// Get Singleton Instances
		Renderer& renderer{ Renderer::Get() };
		SceneManager& sceneManager{ SceneManager::Get() };
		InputManager& inputManager{ InputManager::Get() };
		EventQueue& eventQueue{ EventQueue::Get() };
		Timer& timer{ Timer::Get() };

		if (sceneManager.Empty())
		{
			std::cerr << "ERROR::ENGINE::NO_SCENES_ASSIGNED\n";
			return;
		}

		sceneManager.GameStart();

		while (!inputManager.HasQuit())
		{
			// Timer
			timer.Update();

			// Input
			inputManager.ProcessInput();

			// Fixed Update -> Only For Physics / Networking
			while (timer.GetNeedFixedUpdate())
			{
				sceneManager.FixedUpdate();
			}

			// Update
			sceneManager.Update();

			// LateUpdate
			sceneManager.LateUpdate();

			// EventQueue
			eventQueue.Update();

			// Render
			renderer.Render();

			// FPS Cap
			timer.UpdateFpsCap();
		}
	}

	void Engine::SetGameTitle(const std::string& title)
	{
		SDL_SetWindowTitle(m_pWindow, title.c_str());
	}

	void Engine::SetWindowSize(unsigned int width, unsigned int height)
	{
		SDL_SetWindowSize(m_pWindow, width, height);
		m_WindowWidth = width;
		m_WindowHeight = height;
	}

	void Engine::SetWindowPosition(int x, int y)
	{
		SDL_SetWindowPosition(m_pWindow, x, y);
	}

	void Engine::SetShowCursor(bool showCursor)
	{
		SDL_ShowCursor(showCursor);
	}

	void Engine::PrintSDLVersion()
	{
		printf("\nENGINE INFO:\n");

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

		SDL_MIXER_VERSION(&version);
		printf("We compiled against SDL_mixer version %u.%u.%u ...\n",
			version.major, version.minor, version.patch);

		version = *Mix_Linked_Version();
		printf("We are linking against SDL_mixer version %u.%u.%u.\n",
			version.major, version.minor, version.patch);

		printf("\n");
		printf("GAMEINFO:\n");
	}
}