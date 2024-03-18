#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>
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

	void AddControllerBind(const ControllerInput& input, std::unique_ptr<Command> command);
	void AddKeyboardMouseBind(const KeyBoardInput& input, std::unique_ptr<Command> command);

private:

	bool m_HasQuit;
	std::unique_ptr<Controller> m_Controller;
	std::unique_ptr<KeyboardMouse> m_KeyboardMouse;

};

#endif // !INPUTMANAGER_H