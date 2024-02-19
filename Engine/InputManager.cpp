#include <SDL.h>
#include "InputManager.h"

bool InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		switch (e.type)
		{
		case SDL_QUIT:
			return false;
			break;

		case SDL_KEYDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		default:
			break;
		}
	}
	return true;
}