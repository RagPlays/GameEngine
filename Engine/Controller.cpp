#include "Controller.h"
#include "Command.h"

Controller::Controller()
	: m_CurrentState{ XINPUT_STATE{} }
	, m_PreviousState{ XINPUT_STATE{} }
	, m_ControllerIdx{}
	, m_ButtonsChangedThisFrame{}
	, m_ButtonsPressedthisFrame{}
	, m_ButtonsReleasedthisFrame{}
{
	//AddBind(ControllerInput{XINPUT_GAMEPAD_A, InputType::ispressed}, )
}

void Controller::ProcessInput()
{
	UpdateInputs();

	/*for (const auto& [input, command] : m_InputCommands)
	{
		switch (input.inputType)
		{
		case InputType::ispressed:
			if (IsPressed(input.controllerKey))
			{
				command->Execute();
			}
			break;

		case InputType::wasPressedThisFrame:
			if (WasPressedThisFrame(input.controllerKey))
			{
				command->Execute();
			}
			break;

		case InputType::wasReleasedThisFrame:
			if (WasReleasedThisFrame(input.controllerKey))
			{
				command->Execute();
			}
			break;
		}
	}*/
}

// Private functions //

void Controller::UpdateInputs()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));

	if (XInputGetState(m_ControllerIdx, &m_CurrentState) != ERROR_SUCCESS) return;

	m_ButtonsChangedThisFrame = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedthisFrame = m_ButtonsChangedThisFrame & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedthisFrame = m_ButtonsChangedThisFrame & (~m_CurrentState.Gamepad.wButtons);
}

bool Controller::WasPressedThisFrame(unsigned int button) const
{
	return m_ButtonsPressedthisFrame & button;
}

bool Controller::WasReleasedThisFrame(unsigned int button) const
{
	return m_ButtonsReleasedthisFrame & button;
}

bool Controller::IsPressed(unsigned int button) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}

//void Controller::AddBind(unsigned int inputButton, InputType inputType, Command* command)
//{
//	ControllerInput input{ inputButton, inputType };
//	AddBind(input, command);
//}
//
//void Controller::AddBind(const ControllerInput& input, Command* command)
//{
//	m_InputCommands[input] = command;
//}