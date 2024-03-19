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

//*************************//
//  XinputControllerInput  //
//*************************//

//XinputControllerInput::XinputControllerInput(unsigned int controllerKey)
//	: controllerKey{ controllerKey }
//	, inputType{ InputType::ispressed }
//{
//}
//
//XinputControllerInput::XinputControllerInput(unsigned int controllerKey, InputType inputType)
//	: controllerKey{ controllerKey }
//	, inputType{ inputType }
//{
//}

//*******************//
//  ControllerInput  //
//*******************//

ControllerInput::ControllerInput(SDL_GameControllerButton button)
	: button{ button }
	, inputType{ InputType::ispressed }
{
}

ControllerInput::ControllerInput(SDL_GameControllerButton button, InputType inputType)
	: button{ button }
	, inputType{ inputType }
{
}
