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

	void AddController(int controllerIdx);
	const Controller* GetController(int controllerIdx);
	bool HasController(int controllerIdx);

	void AddKeyboardMouseBind(const KeyBoardInput& input, std::unique_ptr<Command> command);
	void AddControllerBind(const ControllerInput& input, std::unique_ptr<Command> command, int controllerIdx);

private:

	Controller* FindController(int controllerIdx);

private:

	SDL_Event m_Event;
	bool m_HasQuit;
	std::unique_ptr<KeyboardMouse> m_KeyboardMouse;
	std::vector<std::unique_ptr<Controller>> m_Controllers;
};

#endif // !INPUTMANAGER_H