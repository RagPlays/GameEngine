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

	InputManager(const InputManager& other) = delete;
	InputManager(InputManager&& other) noexcept = delete;
	InputManager& operator=(const InputManager& other) = delete;
	InputManager& operator=(InputManager&& other) noexcept = delete;

	void ProcessInput();

	bool HasQuit() const;
	void Quit();

	void AddKeyboardMouseBind(const KeyBoardInput& input, std::unique_ptr<Command> command);
	void AddControllerBind(const ControllerInput& input, std::unique_ptr<Command> command);

private:

	SDL_Event m_Event;
	bool m_HasQuit;
	std::unique_ptr<KeyboardMouse> m_KeyboardMouse;
	std::unique_ptr<Controller> m_Controller;

};

#endif // !INPUTMANAGER_H