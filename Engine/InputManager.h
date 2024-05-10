#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL_events.h>
#include <vector>
#include <memory>

#include "Singleton.h"

class Controller;
class KeyboardMouse;
class Command;

struct KeyBoardInput;
struct ControllerInput;

union SDL_Event;

class InputManager final : public Singleton<InputManager>
{
public:

	virtual ~InputManager();
	InputManager(const InputManager& other) = delete;
	InputManager(InputManager&& other) noexcept = delete;
	InputManager& operator=(const InputManager& other) = delete;
	InputManager& operator=(InputManager&& other) noexcept = delete;

	void ProcessInput();

	bool HasQuit() const;
	void Quit();

	void AddController(int controllerIdx);
	bool HasController(int controllerIdx);
	const Controller* GetController(int controllerIdx) const;
	const KeyboardMouse* GetKeyBoard() const;

	void AddKeyboardMouseBind(const KeyBoardInput& input, std::unique_ptr<Command>&& command);
	void AddControllerBind(const ControllerInput& input, std::unique_ptr<Command>&& command, int controllerIdx);

private:

	friend class Singleton<InputManager>;
	InputManager();

	Controller* FindController(int controllerIdx) const;

private:

	SDL_Event m_Event;
	bool m_HasQuit;
	std::unique_ptr<KeyboardMouse> m_KeyboardMouse;
	std::vector<std::unique_ptr<Controller>> m_Controllers;
};

#endif // !INPUTMANAGER_H