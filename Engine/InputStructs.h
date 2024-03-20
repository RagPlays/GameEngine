#ifndef INPUTSTRUCTS_H
#define INPUTSTRUCTS_H

#include <functional>
#include <SDL.h>
//#include <Windows.h>
//#include <Xinput.h>

enum class InputType
{
	ispressed,
	wasPressedThisFrame,
	wasReleasedThisFrame
};

// KEYBOARD INPUT //
struct KeyBoardInput
{
	explicit KeyBoardInput(SDL_Scancode scancode);
	explicit KeyBoardInput(SDL_Scancode scancode, InputType inputType);

	SDL_Scancode scancode;
	InputType inputType;
};

struct KeyBoardInputHash
{
	size_t operator()(const KeyBoardInput& input) const
	{
		return std::hash<unsigned int>()(input.scancode) ^ std::hash<int>()(static_cast<int>(input.inputType));
	}
};

struct KeyBoardInputEqual
{
	bool operator()(const KeyBoardInput& lhs, const KeyBoardInput& rhs) const
	{
		return lhs.scancode == rhs.scancode && lhs.inputType == rhs.inputType;
	}
};

// CONTROLLER INPUT //
struct ControllerInput
{
	explicit ControllerInput(SDL_GameControllerButton controllerKey);
	explicit ControllerInput(SDL_GameControllerButton, InputType inputType);

	SDL_GameControllerButton button;
	InputType inputType;
};

struct ControllerInputHash
{
	size_t operator()(const ControllerInput& input) const
	{
		return std::hash<int>()(static_cast<int>(input.button)) ^ std::hash<int>()(static_cast<int>(input.inputType));
	}
};

struct ControllerInputEqual
{
	bool operator()(const ControllerInput& lhs, const ControllerInput& rhs) const
	{
		return lhs.button == rhs.button && lhs.inputType == rhs.inputType;
	}
};

#endif // !INPUTSTRUCTS_H