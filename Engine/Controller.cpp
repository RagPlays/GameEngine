#include "Controller.h"

void Controller::ProcessInput()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIdx, &m_CurrentState);
	m_ButtonsChangedThisFrame = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedthisFrame = m_ButtonsChangedThisFrame & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedthisFrame = m_ButtonsChangedThisFrame & (~m_CurrentState.Gamepad.wButtons);
}