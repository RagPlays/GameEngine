#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>
#include "KeyboardMouse.h"
#include "InputManager.h"

KeyboardMouse::KeyboardMouse()
{
	m_CurrentKeyPressed.fill(false);
	m_PreviousKeyPressed.fill(false);

	/*KeyBoardCommandEvent moveUp{ SDL_SCANCODE_W };

	m_KeyboardMouseCommands[]*/
}

void KeyboardMouse::ProcessInput()
{
	std::swap(m_CurrentKeyPressed, m_PreviousKeyPressed);

	// PC Game Inputs
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		UpdateKeyPressed(sdlEvent);
		ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
	}
}

void KeyboardMouse::UpdateKeyPressed(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		m_CurrentKeyPressed[event.key.keysym.scancode] = true;
	}
	else if (event.type == SDL_KEYUP)
	{
		m_CurrentKeyPressed[event.key.keysym.scancode] = false;
	}
}

// Private functions //
bool KeyboardMouse::WasPressedThisFrame(SDL_Scancode key) const
{
	return m_CurrentKeyPressed[key] && !m_PreviousKeyPressed[key];
}

bool KeyboardMouse::WasReleasedThisFrame(SDL_Scancode key) const
{
	return !m_CurrentKeyPressed[key] && m_PreviousKeyPressed[key];
}

bool KeyboardMouse::IsPressed(SDL_Scancode key) const
{
	return m_CurrentKeyPressed[key];
}