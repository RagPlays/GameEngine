#include <backends/imgui_impl_sdl2.h>
#include "ImGuiRenderer.h"
#include "InputManager.h"

InputManager::InputManager()
	: m_HasQuit{ false }
	, m_Event{ SDL_Event{} }
	, m_KeyboardMouse{ std::make_unique<KeyboardMouse>() }
	//, m_XinputController{ std::make_unique<XinputController>() }
	, m_Controller{ std::make_unique<Controller>(0) }
{
}

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
	m_Controller->Update();

	// Process the inputs
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

void InputManager::AddKeyboardMouseBind(const KeyBoardInput& input, std::unique_ptr<Command> command)
{
	m_KeyboardMouse->AddBind(input, std::move(command));
}

void InputManager::AddControllerBind(const ControllerInput& input, std::unique_ptr<Command> command)
{
	m_Controller->AddBind(input, std::move(command));
}