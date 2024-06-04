#ifndef WINLEVELCOMMAND_H
#define	WINLEVELCOMMAND_H

#include "Command.h"
#include "LevelManager.h"
#include "EventIDs.h"

class WinLevelCommand final : public MoE::Command
{
public:

	WinLevelCommand() = default;
	virtual ~WinLevelCommand() = default;

	WinLevelCommand(const WinLevelCommand& other) = delete;
	WinLevelCommand(WinLevelCommand&& other) noexcept = delete;
	WinLevelCommand& operator=(const WinLevelCommand& other) = delete;
	WinLevelCommand& operator=(WinLevelCommand&& other) noexcept = delete;

	void Execute() override
	{
		LevelManager::Get().Notify(nullptr, Event::levelCompleted);
	}
};

#endif // !WINLEVELCOMMAND_H