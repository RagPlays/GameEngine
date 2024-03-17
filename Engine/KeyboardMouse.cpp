#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>

#include "KeyboardMouse.h"
#include "InputManager.h"

void KeyboardMouse::ProcessInput()
{
	// PC Game Inputs
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			InputManager::Get().Quit();
			break;

		case SDL_KEYDOWN:
			break;

		case SDL_KEYUP:
			break;

		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				break;
			case SDL_BUTTON_RIGHT:
				break;
			case SDL_BUTTON_MIDDLE:
				break;
			default:
				break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			break;

		default:
			break;
		}

		// ImGui inputs
		ImGui_ImplSDL2_ProcessEvent(&event);
	}
}