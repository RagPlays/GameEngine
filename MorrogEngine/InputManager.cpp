#include <iostream>
#if defined _DEBUG || defined DEBUG
#include <backends/imgui_impl_sdl2.h>
#endif

#include "InputManager.h"
#include "ImGuiRenderer.h"
#include "Controller.h"
#include "KeyboardMouse.h"

namespace MoE
{
	InputManager::~InputManager() = default;

	void InputManager::ProcessInput()
	{
		while (SDL_PollEvent(&m_Event))
		{
			if (m_Event.type == SDL_QUIT) InputManager::Get().Quit();

#if defined _DEBUG || defined DEBUG
			ImGui_ImplSDL2_ProcessEvent(&m_Event);
#endif
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

	Controller* InputManager::AddController(int controllerIdx)
	{
		if (HasController(controllerIdx))
		{
			std::cerr << "INPUTMANAGER::ADDCONTROLLER::CONTROLLER_ALREADY_EXISTS\n";
			return GetController(controllerIdx);
		}
		auto controller{ std::make_unique<Controller>(controllerIdx) };
		auto controllerPtr{ controller.get() };
		m_Controllers.emplace_back(std::move(controller));
		return controllerPtr;
	}

	bool InputManager::HasController(int controllerIdx)
	{
		return FindController(controllerIdx) != nullptr;
	}

	Controller* InputManager::GetController(int controllerIdx) const
	{
		Controller* controller{ FindController(controllerIdx) };
		if (!controller) std::cerr << "INPUTMANAGER::GETCONTROLLER::CONTROLLERIDX_NOT_FOUND\n";
		return controller;
	}

	const KeyboardMouse* InputManager::GetKeyBoard() const
	{
		return m_KeyboardMouse.get();
	}

	void InputManager::AddKeyboardMouseBind(const KeyBoardInput& input, std::unique_ptr<Command>&& command)
	{
		m_KeyboardMouse->AddBind(input, std::move(command));
	}

	void InputManager::AddControllerBind(const ControllerInput& input, std::unique_ptr<Command>&& command, int controllerIdx)
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

	void InputManager::ClearBinds()
	{
		m_KeyboardMouse->ClearBinds();
		m_Controllers.clear();
	}

	// Private Functions //

	InputManager::InputManager()
		: m_Event{}
		, m_HasQuit{}
		, m_KeyboardMouse{ std::make_unique<KeyboardMouse>() }
		, m_Controllers{}
	{
	}

	Controller* InputManager::FindController(int controllerIdx) const
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
}