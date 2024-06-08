#ifndef QUITGAMECOMMAND_H
#define QUITGAMECOMMAND_H

#include "Command.h"
#include "InputManager.h"

class QuitGameCommand final : public MoE::Command
{
public:

	QuitGameCommand() = default;
	~QuitGameCommand() = default;

	QuitGameCommand(const QuitGameCommand& other) = delete;
	QuitGameCommand(QuitGameCommand&& other) noexcept = delete;
	QuitGameCommand& operator=(const QuitGameCommand& other) = delete;
	QuitGameCommand& operator=(QuitGameCommand&& other) noexcept = delete;

	virtual void Execute() override
	{
		MoE::InputManager::Get().Quit();
	}

};

#endif // !QUITGAMECOMMAND_H