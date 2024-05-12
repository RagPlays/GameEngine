#ifndef NEXTLEVELCOMMAND_H
#define NEXTLEVELCOMMAND_H

#include "Command.h"
#include "LevelManager.h"

class NextLevelCommand final : public MoE::Command
{
public:

	NextLevelCommand() = default;
	~NextLevelCommand() = default;

	NextLevelCommand(const NextLevelCommand& other) = delete;
	NextLevelCommand(NextLevelCommand&& other) noexcept = delete;
	NextLevelCommand& operator=(const NextLevelCommand& other) = delete;
	NextLevelCommand& operator=(NextLevelCommand&& other) noexcept = delete;

	void Execute() override
	{
		LevelManager::Get().NextLevel();
	}

};

#endif // !NEXTLEVELCOMMAND_H
