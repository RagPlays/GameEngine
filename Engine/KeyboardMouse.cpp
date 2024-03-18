#include <backends/imgui_impl_sdl2.h>
#include "KeyboardMouse.h"
#include "InputManager.h"

KeyboardMouse::KeyboardMouse()
	: m_Event{ SDL_Event{} }
{
	m_CurrentKeyStates.reserve(SDL_NUM_SCANCODES);
	m_CurrentKeyStates.assign(SDL_GetKeyboardState(nullptr), SDL_GetKeyboardState(nullptr) + SDL_NUM_SCANCODES);
	m_PreviousKeyStates.reserve(SDL_NUM_SCANCODES);
}

void KeyboardMouse::ProcessInput()
{
	SDL_PumpEvents();  // Update the state of the keys
	m_CurrentKeyStates.assign(SDL_GetKeyboardState(nullptr), SDL_GetKeyboardState(nullptr) + SDL_NUM_SCANCODES);

	// PC Game Inputs
	while (SDL_PollEvent(&m_Event))
	{
		if (m_Event.type == SDL_QUIT) InputManager::Get().Quit();

		ImGui_ImplSDL2_ProcessEvent(&m_Event);
	}

	// Go over all commands
	for (const auto& [input, command] : m_Commands)
	{
		switch (input.inputType)
		{
		case InputType::ispressed:
			if (IsPressed(input.scancode))
			{
				command->Execute();
			}
			break;

		case InputType::wasPressedThisFrame:
			if (WasPressedThisFrame(input.scancode))
			{
				command->Execute();
			}
			break;

		case InputType::wasReleasedThisFrame:
			if (WasReleasedThisFrame(input.scancode))
			{
				command->Execute();
			}
			break;
		}
	}

	// swap the values
	std::swap(m_PreviousKeyStates, m_CurrentKeyStates);
}

void KeyboardMouse::AddBind(const KeyBoardInput& input, std::unique_ptr<Command> command)
{
	m_Commands[input] = std::move(command);
}

// Private functions //
bool KeyboardMouse::WasPressedThisFrame(SDL_Scancode key) const
{
	return m_CurrentKeyStates[key] && !m_PreviousKeyStates[key];
}

bool KeyboardMouse::WasReleasedThisFrame(SDL_Scancode key) const
{
	return !m_CurrentKeyStates[key] && m_PreviousKeyStates[key];
}

bool KeyboardMouse::IsPressed(SDL_Scancode key) const
{
	return m_CurrentKeyStates[key];
}