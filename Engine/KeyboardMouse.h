#ifndef KEYBOARDMOUSE_H
#define KEYBOARDMOUSE_H

#include <memory>
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

	void Update();
	void ProcessInput();

	void AddBind(const KeyBoardInput& input, std::unique_ptr<Command> command);

private:

	bool WasPressedThisFrame(SDL_Scancode key) const;
	bool WasReleasedThisFrame(SDL_Scancode key) const;
	bool IsPressed(SDL_Scancode key) const;

private:

	std::vector<uint8_t> m_CurrentKeyStates;
	std::vector<uint8_t> m_PreviousKeyStates;

	std::unordered_map<KeyBoardInput, std::unique_ptr<Command>, KeyBoardInputHash, KeyBoardInputEqual> m_Commands;

	std::vector<SDL_Scancode> m_KeyStack;
};

#endif // !KEYBOARDMOUSE_H