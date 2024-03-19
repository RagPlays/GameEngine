//#include "XinputController.h"
//
//XinputController::XinputController()
//	: m_CurrentState{ XINPUT_STATE{} }
//	, m_PreviousState{ XINPUT_STATE{} }
//	, m_ControllerIdx{}
//	, m_ButtonsChangedThisFrame{}
//	, m_ButtonsPressedthisFrame{}
//	, m_ButtonsReleasedthisFrame{}
//{
//}
//
//void XinputController::Update()
//{
//	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
//	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
//
//	if (XInputGetState(m_ControllerIdx, &m_CurrentState) != ERROR_SUCCESS) return;
//
//	m_ButtonsChangedThisFrame = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
//	m_ButtonsPressedthisFrame = m_ButtonsChangedThisFrame & m_CurrentState.Gamepad.wButtons;
//	m_ButtonsReleasedthisFrame = m_ButtonsChangedThisFrame & (~m_CurrentState.Gamepad.wButtons);
//}
//
//void XinputController::ProcessInput()
//{
//	for (const auto& [input, command] : m_Commands)
//	{
//		switch (input.inputType)
//		{
//		case InputType::ispressed:
//			if (IsPressed(input.controllerKey))
//			{
//				command->Execute();
//			}
//			break;
//
//		case InputType::wasPressedThisFrame:
//			if (WasPressedThisFrame(input.controllerKey))
//			{
//				command->Execute();
//			}
//			break;
//
//		case InputType::wasReleasedThisFrame:
//			if (WasReleasedThisFrame(input.controllerKey))
//			{
//				command->Execute();
//			}
//			break;
//		}
//
//	}
//}
//
//void XinputController::AddBind(const XinputControllerInput& input, std::unique_ptr<Command> command)
//{
//	m_Commands[input] = std::move(command);
//}
//
//// Private functions //
//
//bool XinputController::WasPressedThisFrame(unsigned int button) const
//{
//	return m_ButtonsPressedthisFrame & button;
//}
//
//bool XinputController::WasReleasedThisFrame(unsigned int button) const
//{
//	return m_ButtonsReleasedthisFrame & button;
//}
//
//bool XinputController::IsPressed(unsigned int button) const
//{
//	return m_CurrentState.Gamepad.wButtons & button;
//}