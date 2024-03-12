#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>
#include "InputManager.h"

#include <iostream>

bool InputManager::ProcessInput()
{

	if (IsDownThisFrame(buttonsPressedThisFrame, XINPUT_GAMEPAD_A))
	{
		std::cout << "A";
	}
	if (IsDownThisFrame(buttonsPressedThisFrame, XINPUT_GAMEPAD_B))
	{
		std::cout << "B";
	}
	if (IsDownThisFrame(buttonsPressedThisFrame, XINPUT_GAMEPAD_X))
	{
		std::cout << "X";
	}
	if (IsDownThisFrame(buttonsPressedThisFrame, XINPUT_GAMEPAD_Y))
	{
		std::cout << "Y";
	}

	if (IsUpThisFrame(buttonsReleasedThisFrame, XINPUT_GAMEPAD_A))
	{
		std::cout << "Ar";
	}
	if (IsUpThisFrame(buttonsReleasedThisFrame, XINPUT_GAMEPAD_B))
	{
		std::cout << "Br";
	}
	if (IsUpThisFrame(buttonsReleasedThisFrame, XINPUT_GAMEPAD_X))
	{
		std::cout << "Xr";
	}
	if (IsUpThisFrame(buttonsReleasedThisFrame, XINPUT_GAMEPAD_Y))
	{
		std::cout << "Yr";
	}
	

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		// PC Game Inputs
		switch (event.type)
		{
		case SDL_QUIT:
			return false;
			break;

		case SDL_KEYDOWN:
			break;

		case SDL_KEYUP:
			break;

		case SDL_MOUSEBUTTONUP:
			break;

		case SDL_MOUSEBUTTONDOWN:
			break;

		default:
			break;
		}

		// ImGui inputs
		ImGui_ImplSDL2_ProcessEvent(&event);
	}
	return true;
}