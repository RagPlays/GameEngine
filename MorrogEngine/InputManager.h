#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL_events.h>
#include <vector>
#include <memory>

#include "Singleton.h"

union SDL_Event;

namespace MoE
{
	class Controller;
	class KeyboardMouse;
	class Command;

	struct KeyBoardInput;
	struct ControllerInput;

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

		Controller* AddController(int controllerIdx);
		bool HasController(int controllerIdx);
		Controller* GetController(int controllerIdx) const;
		const KeyboardMouse* GetKeyBoard() const;

		void AddKeyboardMouseBind(const KeyBoardInput& input, std::unique_ptr<Command>&& command);
		void AddControllerBind(const ControllerInput& input, std::unique_ptr<Command>&& command, int controllerIdx);

		void ClearBinds();

	private:

		friend class MoE::Singleton<InputManager>;
		InputManager();

		Controller* FindController(int controllerIdx) const;

	private:

		SDL_Event m_Event;
		bool m_HasQuit;
		std::unique_ptr<KeyboardMouse> m_KeyboardMouse;
		std::vector<std::unique_ptr<Controller>> m_Controllers;

	};
}

#endif // !INPUTMANAGER_H