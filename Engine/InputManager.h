#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <memory>
#include "Singleton.h"
#include "Controller.h"
#include "KeyboardMouse.h"

class InputManager final : public Singleton<InputManager>
{
public:
	InputManager();
	~InputManager() = default;

	void ProcessInput();

	bool HasQuit() const;
	void Quit();

	//void AddKeyboardMouseBind(); // SDL_Key/SDL_MouseBotton + SDL_EventType
	//void AddControllerBind();

private:
	bool m_HasQuit;
	std::unique_ptr<Controller> m_Controller;
	std::unique_ptr<KeyboardMouse> m_KeyboardMouse;
};

#endif // !INPUTMANAGER_H