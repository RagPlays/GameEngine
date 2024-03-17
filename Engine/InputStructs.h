#ifndef INPUTSTRUCTS_H
#define INPUTSTRUCTS_H

#include <SDL.h>
#include <Windows.h>
#include <Xinput.h>

enum class InputType
{
	ispressed,
	wasPressedThisFrame,
	wasReleasedThisFrame
};

struct KeyBoardInput
{
	explicit KeyBoardInput(SDL_Scancode scancode);
	explicit KeyBoardInput(SDL_Scancode scancode, InputType inputType);

	SDL_Scancode scancode;
	InputType inputType;
};

struct ControllerInput
{
	explicit ControllerInput(unsigned int controllerKey);
	explicit ControllerInput(unsigned int controllerKey, InputType inputType);

	unsigned int controllerKey;
	InputType inputType;
};

#endif // !INPUTSTRUCTS_H