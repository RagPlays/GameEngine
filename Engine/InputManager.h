#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <Windows.h>
#include <Xinput.h>
#include "Singleton.h"

#pragma comment(lib, "xinput.lib")

class InputManager final : public Singleton<InputManager>
{
public:
	bool ProcessInput();

private:

	XINPUT_STATE m_CurrentState;
	XINPUT_STATE m_PreviousState;
	unsigned int m_ControllerIdx;
	unsigned int m_ButtonsPressedthisFrame;
};

inline bool IsDownThisFrame(unsigned int buttonsPressed, unsigned int button)
{
	return buttonsPressed & button;
}
inline bool IsUpThisFrame(unsigned int buttonsReleased, unsigned int button)
{
	return buttonsReleased & button;
}


#endif // !INPUTMANAGER_H