#include "InputStructs.h"

//*****************//
//  KeyBoardInput  //
//*****************//

KeyBoardInput::KeyBoardInput(SDL_Scancode scancode)
	: scancode{ scancode }
	, inputType{ InputType::ispressed }
{
}

KeyBoardInput::KeyBoardInput(SDL_Scancode scancode, InputType inputType)
	: scancode{ scancode }
	, inputType{ inputType }
{
}

//*******************//
//  ControllerInput  //
//*******************//

ControllerInput::ControllerInput(unsigned int controllerKey)
	: controllerKey{ controllerKey }
	, inputType{ InputType::ispressed }
{
}

ControllerInput::ControllerInput(unsigned int controllerKey, InputType inputType)
	: controllerKey{ controllerKey }
	, inputType{ inputType }
{
}
