#ifndef CONTROLLERINPUT_H
#define CONTROLLERINPUT_H

#include <Windows.h>
#include <Xinput.h>

class Controller final
{
public:
	Controller() = default;
	~Controller() = default;

	Controller(const Controller& other) = delete;
	Controller(Controller&& other) noexcept = delete;
	Controller& operator=(const Controller& other) = delete;
	Controller& operator=(Controller&& other) noexcept = delete;

	void ProcessInput();

private:

	XINPUT_STATE m_CurrentState;
	XINPUT_STATE m_PreviousState;
	unsigned int m_ControllerIdx;
	unsigned int m_ButtonsChangedThisFrame;
	unsigned int m_ButtonsPressedthisFrame;
	unsigned int m_ButtonsReleasedthisFrame;
};

#endif // !CONTROLLERINPUT_H