#include "InputManager.h"

InputManager::InputManager()
	: m_HasQuit{ false }
	, m_Controller{ std::make_unique<Controller>() }
	, m_KeyboardMouse{ std::make_unique<KeyboardMouse>() }
{
}

void InputManager::ProcessInput()
{
	m_KeyboardMouse->ProcessInput();
	m_Controller->ProcessInput();
}

bool InputManager::HasQuit() const
{
	return m_HasQuit;
}

void InputManager::Quit()
{
	m_HasQuit = true;
}

void InputManager::AddControllerBind(const ControllerInput& input, std::unique_ptr<Command> command)
{
	m_Controller->AddBind(input, std::move(command));
}

void InputManager::AddKeyboardMouseBind(const KeyBoardInput& input, std::unique_ptr<Command> command)
{
	m_KeyboardMouse->AddBind(input, std::move(command));
}