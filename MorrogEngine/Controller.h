#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <vector>
#include <unordered_map>

#include "InputStructs.h"
#include "Command.h"

namespace MoE
{
	class Command;

	enum class ControllerButton;
	enum class KeyBoardButton;
	enum class InputType;

	class Controller final
	{
	public:

		explicit Controller(int controllerIndx);
		~Controller();

		Controller(const Controller& other) = delete;
		Controller(Controller&& other) noexcept = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;

		void Update();
		void ProcessInput();

		void AddBind(const ControllerInput& input, std::unique_ptr<Command>&& command);

		SDL_GameController* GetGameController() const;
		int GetControllerIdx() const;

	private:

		bool WasPressedThisFrame(ControllerButton button) const;
		bool WasReleasedThisFrame(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;

		static uint8_t GameControllerGetButton(SDL_GameController* gameController, ControllerButton controllerbutton);

	private:

		SDL_GameController* m_GameController;
		int m_ControllerIdx;
		std::vector<uint8_t> m_CurrentButtonStates;
		std::vector<uint8_t> m_PreviousButtonStates;
		std::unordered_map<ControllerInput, std::unique_ptr<Command>, ControllerInputHash, ControllerInputEqual> m_Commands;

	};
}

#endif // !CONTROLLER_H