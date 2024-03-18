#ifndef CONTROLLERINPUT_H
#define CONTROLLERINPUT_H

#include <memory>
#include <unordered_map>
#include "InputStructs.h"
#include "Command.h"

class Controller final
{
public:

	Controller();
	~Controller() = default;

	Controller(const Controller& other) = delete;
	Controller(Controller&& other) noexcept = delete;
	Controller& operator=(const Controller& other) = delete;
	Controller& operator=(Controller&& other) noexcept = delete;

	void ProcessInput();

	void AddBind(const ControllerInput& input, std::unique_ptr<Command> command);

private:

	void UpdateInputs();

	bool WasPressedThisFrame(unsigned int button) const;
	bool WasReleasedThisFrame(unsigned int button) const;
	bool IsPressed(unsigned int button) const;

private:

	XINPUT_STATE m_CurrentState;
	XINPUT_STATE m_PreviousState;
	unsigned int m_ControllerIdx;
	unsigned int m_ButtonsChangedThisFrame;
	unsigned int m_ButtonsPressedthisFrame;
	unsigned int m_ButtonsReleasedthisFrame;

	std::unordered_map<ControllerInput, std::unique_ptr<Command>, ControllerInputHash, ControllerInputEqual> m_Commands;
};

#endif // !CONTROLLERINPUT_H