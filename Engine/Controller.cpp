#include <cassert>
#include <iostream>
#include <algorithm>
#include "Controller.h"

Controller::Controller(int controllerIndx)
	: m_ControllerIdx{ controllerIndx }
	, m_GameController{ SDL_GameControllerOpen(controllerIndx) }
{
    if (!m_GameController)
    {
        std::cerr << "CONTROLLER::CONTROLLER::COULD_NOT_FIND_CONTROLLER_ON_START_WITH_IDX_" << m_ControllerIdx << "\n";
    }

    m_CurrentButtonStates.resize(SDL_CONTROLLER_BUTTON_MAX, SDL_GameControllerGetButton(m_GameController, SDL_CONTROLLER_BUTTON_INVALID));
    m_PreviousButtonStates.resize(SDL_CONTROLLER_BUTTON_MAX, SDL_GameControllerGetButton(m_GameController, SDL_CONTROLLER_BUTTON_INVALID));
}

Controller::~Controller()
{
	if(m_GameController) SDL_GameControllerClose(m_GameController);
}

void Controller::Update()
{
    // check
    if (!m_GameController) return;

    // Update the button states.
    std::transform(m_CurrentButtonStates.begin(), m_CurrentButtonStates.end(), m_CurrentButtonStates.begin(),
        [&](const Uint8& state) 
        {
            SDL_GameControllerButton button = static_cast<SDL_GameControllerButton>(&state - &m_CurrentButtonStates[0]);
            return SDL_GameControllerGetButton(m_GameController, button);
        }
    );
}

void Controller::ProcessInput()
{
    // check
    if (!m_GameController) return;

    // Go over all commands
    for (const auto& [input, command] : m_Commands)
    {
        switch (input.inputType)
        {
        case InputType::ispressed:
            if (IsPressed(input.button)) command->Execute();
            break;

        case InputType::wasPressedThisFrame:
            if (WasPressedThisFrame(input.button)) command->Execute();
            break;

        case InputType::wasReleasedThisFrame:
            if (WasReleasedThisFrame(input.button)) command->Execute();
            break;
        }
    }

    // Swap the values
    std::swap(m_PreviousButtonStates, m_CurrentButtonStates);
}

void Controller::AddBind(const ControllerInput& input, std::unique_ptr<Command> command)
{
    m_Commands[input] = std::move(command);
}

SDL_GameController* Controller::GetGameController() const
{
	return m_GameController;
}

int Controller::GetControllerIdx() const
{
	return m_ControllerIdx;
}

bool Controller::WasPressedThisFrame(SDL_GameControllerButton button) const
{
    return m_CurrentButtonStates[button] && !m_PreviousButtonStates[button];
}

bool Controller::WasReleasedThisFrame(SDL_GameControllerButton button) const
{
    return !m_CurrentButtonStates[button] && m_PreviousButtonStates[button];
}

bool Controller::IsPressed(SDL_GameControllerButton button) const
{
    if (button == SDL_CONTROLLER_BUTTON_INVALID) return false;
    return m_CurrentButtonStates[button];
}