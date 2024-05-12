#include <functional>

#include "InputStructs.h"
#include "InputCodes.h"

namespace MoE
{
	//*****************//
	//  KeyBoardInput  //
	//*****************//

	KeyBoardInput::KeyBoardInput(KeyBoardButton scancode)
		: scancode{ scancode }
		, inputType{ InputType::ispressed }
	{
	}

	KeyBoardInput::KeyBoardInput(KeyBoardButton scancode, InputType inputType)
		: scancode{ scancode }
		, inputType{ inputType }
	{
	}

	size_t KeyBoardInputHash::operator()(const KeyBoardInput& input) const
	{
		return std::hash<unsigned int>()
			(static_cast<unsigned int>(input.scancode)) ^ std::hash<unsigned int>()(static_cast<int>(input.inputType));
	}

	bool KeyBoardInputEqual::operator()(const KeyBoardInput& lhs, const KeyBoardInput& rhs) const
	{
		return lhs.scancode == rhs.scancode && lhs.inputType == rhs.inputType;
	}

	//*******************//
	//  ControllerInput  //
	//*******************//

	ControllerInput::ControllerInput(ControllerButton button)
		: button{ button }
		, inputType{ InputType::ispressed }
	{
	}

	ControllerInput::ControllerInput(ControllerButton button, InputType inputType)
		: button{ button }
		, inputType{ inputType }
	{
	}

	size_t ControllerInputHash::operator()(const ControllerInput& input) const
	{
		return std::hash<unsigned int>()
			(static_cast<unsigned int>(input.button)) ^ std::hash<unsigned int>()(static_cast<int>(input.inputType));
	}

	bool ControllerInputEqual::operator()(const ControllerInput& lhs, const ControllerInput& rhs) const
	{
		return lhs.button == rhs.button && lhs.inputType == rhs.inputType;
	}
}