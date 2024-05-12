#ifndef INPUTSTRUCTS_H
#define INPUTSTRUCTS_H

namespace MoE
{
	enum class ControllerButton;
	enum class KeyBoardButton;
	enum class InputType;

	// KEYBOARD INPUT //
	struct KeyBoardInput
	{
		explicit KeyBoardInput(KeyBoardButton scancode);
		explicit KeyBoardInput(KeyBoardButton scancode, InputType inputType);

		KeyBoardButton scancode;
		InputType inputType;
	};

	struct KeyBoardInputHash
	{
		size_t operator()(const KeyBoardInput& input) const;
	};

	struct KeyBoardInputEqual
	{
		bool operator()(const KeyBoardInput& lhs, const KeyBoardInput& rhs) const;
	};

	// CONTROLLER INPUT //
	struct ControllerInput
	{
		explicit ControllerInput(ControllerButton controllerKey);
		explicit ControllerInput(ControllerButton, InputType inputType);

		ControllerButton button;
		InputType inputType;
	};

	struct ControllerInputHash
	{
		size_t operator()(const ControllerInput& input) const;
	};

	struct ControllerInputEqual
	{
		bool operator()(const ControllerInput& lhs, const ControllerInput& rhs) const;
	};
}

#endif // !INPUTSTRUCTS_H