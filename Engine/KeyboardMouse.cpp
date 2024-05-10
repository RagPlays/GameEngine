#include "KeyboardMouse.h"
#include "InputManager.h"
#include "Command.h"

#include "InputCodes.h"

KeyboardMouse::KeyboardMouse()
{
	m_CurrentKeyStates.assign(SDL_GetKeyboardState(nullptr), SDL_GetKeyboardState(nullptr) + SDL_NUM_SCANCODES);
	m_PreviousKeyStates.assign(SDL_GetKeyboardState(nullptr), SDL_GetKeyboardState(nullptr) + SDL_NUM_SCANCODES);
	m_KeyStack.reserve(4);
}

void KeyboardMouse::Update()
{
	m_CurrentKeyStates.assign(SDL_GetKeyboardState(nullptr), SDL_GetKeyboardState(nullptr) + SDL_NUM_SCANCODES);
}

void KeyboardMouse::ProcessInput()
{
	// Go over all commands
	for (const auto& [input, command] : m_Commands)
	{
		switch (input.inputType)
		{
		case InputType::ispressed:
			if(WasPressedThisFrame(input.scancode)) m_KeyStack.emplace_back(input.scancode);
			if (IsPressed(input.scancode))
			{
				if (input.scancode == m_KeyStack.back())
				{
					command->Execute();
				}
			}
			break;

		case InputType::wasPressedThisFrame:
			if (WasPressedThisFrame(input.scancode))
			{
				m_KeyStack.emplace_back(input.scancode);
				command->Execute();
			}
			break;

		case InputType::wasReleasedThisFrame:
			if (WasReleasedThisFrame(input.scancode))
			{
				m_KeyStack.erase(std::remove(m_KeyStack.begin(), m_KeyStack.end(), input.scancode), m_KeyStack.end());
				command->Execute();
			}
			break;
		}
	}

	// swap the values
	std::swap(m_PreviousKeyStates, m_CurrentKeyStates);
}

void KeyboardMouse::AddBind(const KeyBoardInput& input, std::unique_ptr<Command>&& command)
{
	m_Commands[input] = std::move(command);
}

// Private functions //
bool KeyboardMouse::WasPressedThisFrame(KeyBoardButton key) const
{
	const int keyIdx{ static_cast<int>(key) };
	return m_CurrentKeyStates[keyIdx] && !m_PreviousKeyStates[keyIdx];
}

bool KeyboardMouse::WasReleasedThisFrame(KeyBoardButton key) const
{
	const int keyIdx{ static_cast<int>(key) };
	return !m_CurrentKeyStates[keyIdx] && m_PreviousKeyStates[keyIdx];
}

bool KeyboardMouse::IsPressed(KeyBoardButton key) const
{
	const int keyIdx{ static_cast<int>(key) };
	return m_CurrentKeyStates[keyIdx];
}