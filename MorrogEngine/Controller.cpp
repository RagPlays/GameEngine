#include <cassert>
#include <iostream>
#include <algorithm>

#include <SDL_events.h>

#include "Controller.h"
#include "InputCodes.h"

Controller::Controller(int controllerIndx)
	: m_ControllerIdx{ controllerIndx }
	, m_GameController{ SDL_GameControllerOpen(controllerIndx) }
{
    if (!m_GameController)
    {
        std::cerr << "CONTROLLER::CONTROLLER::COULD_NOT_FIND_CONTROLLER_ON_START_WITH_IDX_" << m_ControllerIdx << "\n";
    }

    m_CurrentButtonStates.resize(
        static_cast<uint8_t>(ControllerButton::CB_MAX), GameControllerGetButton(m_GameController, ControllerButton::CB_INVALID));
    m_PreviousButtonStates.resize(
        static_cast<uint8_t>(ControllerButton::CB_MAX), GameControllerGetButton(m_GameController, ControllerButton::CB_INVALID));
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

void Controller::AddBind(const ControllerInput& input, std::unique_ptr<Command>&& command)
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

bool Controller::WasPressedThisFrame(ControllerButton button) const
{
    const int buttonIdx{static_cast<int>(button) };
    return m_CurrentButtonStates[buttonIdx] && !m_PreviousButtonStates[buttonIdx];
}

bool Controller::WasReleasedThisFrame(ControllerButton button) const
{
    const int buttonIdx{ static_cast<int>(button) };
    return !m_CurrentButtonStates[buttonIdx] && m_PreviousButtonStates[buttonIdx];
}

bool Controller::IsPressed(ControllerButton button) const
{
    if (button == ControllerButton::CB_INVALID) return false;
    const int buttonIdx{ static_cast<int>(button) };
    return m_CurrentButtonStates[buttonIdx];
}

uint8_t Controller::GameControllerGetButton(SDL_GameController* gameController, ControllerButton controllerbutton)
{
    return static_cast<uint8_t>
        (
            SDL_GameControllerGetButton(
                gameController,
                static_cast<SDL_GameControllerButton>(controllerbutton)
            )
        );
}