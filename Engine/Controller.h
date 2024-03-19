#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <vector>
#include <unordered_map>
#include "InputStructs.h"
#include "Command.h"

class Controller final
{
public:

	Controller(int controllerIndx);
	~Controller();

	Controller(const Controller& other) = delete;
	Controller(Controller&& other) noexcept = delete;
	Controller& operator=(const Controller& other) = delete;
	Controller& operator=(Controller&& other) = delete;

	void Update();
	void ProcessInput();

	void AddBind(const ControllerInput& input, std::unique_ptr<Command> command);

	SDL_GameController* GetGameController() const;
	int GetControllerIdx() const;

private:

	bool WasPressedThisFrame(SDL_GameControllerButton button) const;
	bool WasReleasedThisFrame(SDL_GameControllerButton button) const;
	bool IsPressed(SDL_GameControllerButton button) const;

private:

	SDL_GameController* m_GameController;
	int m_ControllerIdx;
	std::vector<Uint8> m_CurrentButtonStates;
	std::vector<Uint8> m_PreviousButtonStates;
	std::unordered_map<ControllerInput, std::unique_ptr<Command>, ControllerInputHash, ControllerInputEqual> m_Commands;

};

#endif // !CONTROLLER_H