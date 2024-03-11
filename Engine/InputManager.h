#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

//#include <Xinput.h>
//#include <minwinbase.h>
#include "Singleton.h"

class InputManager final : public Singleton<InputManager>
{
public:
	bool ProcessInput();

private:

	/*XINPUT_STATE m_CurrentState;
	XINPUT_STATE m_PreviousState;
	unsigned int m_ControllerIdx;*/
};

#endif // !INPUTMANAGER_H