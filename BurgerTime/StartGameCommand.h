#ifndef STARTGAMECOMMAND_H
#define STARTGAMECOMMAND_H

#include "Command.h"
#include "LevelManager.h"

class StartGameCommand final : public MoE::Command
{
public:

	StartGameCommand() = default;
	virtual ~StartGameCommand() = default;

	StartGameCommand(const StartGameCommand& other) = delete;
	StartGameCommand(StartGameCommand&& other) noexcept = delete;
	StartGameCommand& operator=(const StartGameCommand& other) = delete;
	StartGameCommand& operator=(StartGameCommand&& other) noexcept = delete;

	void Execute() override
	{
		LevelManager::Get().GoInfoMenu();
	}

};

#endif // !STARTGAMECOMMAND_H
