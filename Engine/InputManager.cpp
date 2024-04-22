#include <backends/imgui_impl_sdl2.h>
#include <iostream>
#include "ImGuiRenderer.h"
#include "InputManager.h"

void InputManager::ProcessInput()
{
	// Update the state of the keys
	SDL_PumpEvents();

	// PC Game Inputs
	while (SDL_PollEvent(&m_Event))
	{
		if (m_Event.type == SDL_QUIT) InputManager::Get().Quit();
		
		if (ImGuiRenderer::Get().IsEnabled())
		{
			ImGui_ImplSDL2_ProcessEvent(&m_Event);
		}
	}

	// Update all inputs 
	m_KeyboardMouse->Update();
	for (auto& controller : m_Controllers)
	{
		controller->Update();
	}

	// Process the inputs
	m_KeyboardMouse->ProcessInput();
	for (auto& controller : m_Controllers)
	{
		controller->ProcessInput();
	}
}

bool InputManager::HasQuit() const
{
	return m_HasQuit;
}

void InputManager::Quit()
{
	m_HasQuit = true;
}

void InputManager::AddController(int controllerIdx)
{
	if (HasController(controllerIdx))
	{
		std::cerr << "INPUTMANAGER::ADDCONTROLLER::CONTROLLER_ALREADY_EXISTS\n";
		return;
	}
	m_Controllers.emplace_back(std::make_unique<Controller>(controllerIdx));
}

const Controller* InputManager::GetController(int controllerIdx)
{
	Controller* controller{ FindController(controllerIdx) };

	if(!controller) std::cerr << "INPUTMANAGER::GETCONTROLLER::CONTROLLERIDX_NOT_FOUND\n";

	return controller;
}

bool InputManager::HasController(int controllerIdx)
{
	return FindController(controllerIdx) != nullptr;
}

void InputManager::AddKeyboardMouseBind(const KeyBoardInput& input, std::unique_ptr<Command> command)
{
	m_KeyboardMouse->AddBind(input, std::move(command));
}

void InputManager::AddControllerBind(const ControllerInput& input, std::unique_ptr<Command> command, int controllerIdx)
{
	for (size_t idx{}; idx < m_Controllers.size(); ++idx)
	{
		if (m_Controllers[idx]->GetControllerIdx() == controllerIdx)
		{
			m_Controllers[idx]->AddBind(input, std::move(command));
			return;
		}
	}
	std::cerr << "INPUTMANAGER::ADDCONTROLLERBIND::CONTROLLERIDX_NOT_FOUND\n";
}

// Private Functions //

InputManager::InputManager()
	: m_HasQuit{ false }
	, m_Event{ SDL_Event{} }
	, m_KeyboardMouse{ std::make_unique<KeyboardMouse>() }
{
}

Controller* InputManager::FindController(int controllerIdx)
{
	for (const auto& controller : m_Controllers)
	{
		if (controller->GetControllerIdx() == controllerIdx)
		{
			return controller.get();
		}
	}
	return nullptr;
}
