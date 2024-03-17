#ifndef KEYBOARDMOUSE_H
#define KEYBOARDMOUSE_H

#include <array>
#include <unordered_map>

#include "InputStructs.h"

class Command;

class KeyboardMouse final
{
public:

	KeyboardMouse();
	~KeyboardMouse() = default;

	KeyboardMouse(const KeyboardMouse& other) = delete;
	KeyboardMouse(KeyboardMouse&& other) noexcept = delete;
	KeyboardMouse& operator=(const KeyboardMouse& other) = delete;
	KeyboardMouse& operator=(KeyboardMouse&& other) noexcept = delete;

	void ProcessInput();

private:

	void UpdateKeyPressed(const SDL_Event& event);

	bool WasPressedThisFrame(SDL_Scancode key) const;
	bool WasReleasedThisFrame(SDL_Scancode key) const;
	bool IsPressed(SDL_Scancode key) const;

private:

	std::array<bool, SDL_NUM_SCANCODES> m_CurrentKeyPressed;
	std::array<bool, SDL_NUM_SCANCODES> m_PreviousKeyPressed;

	//td::unordered_map<KeyBoardCommandEvent, Command*> m_KeyboardMouseCommands;
};

#endif // !KEYBOARDMOUSE_H