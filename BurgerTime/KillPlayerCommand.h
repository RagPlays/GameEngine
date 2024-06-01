#ifndef KILLPLAYERCOMMAND_H
#define KILLPLAYERCOMMAND_H

#include "PlayerCommand.h"
#include "Player.h"

class KillPlayerCommand final : public PlayerCommand
{
public:

	explicit KillPlayerCommand(Player* player)
		: PlayerCommand{ player }
	{
	}
	virtual ~KillPlayerCommand() = default;

	KillPlayerCommand(const KillPlayerCommand& other) = delete;
	KillPlayerCommand(KillPlayerCommand&& other) noexcept = delete;
	KillPlayerCommand& operator=(const KillPlayerCommand& other) = delete;
	KillPlayerCommand& operator=(KillPlayerCommand&& other) noexcept = delete;

	virtual void Execute() override
	{
		if (GetPlayer())
		{
			GetPlayer()->Kill();
		}
	}

};

#endif // !KILLPLAYERCOMMAND_H
