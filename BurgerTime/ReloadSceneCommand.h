#ifndef RELOADSCENECOMMAND_H
#define RELOADSCENECOMMAND_H

#include "Command.h"
#include "SceneManager.h"

class ReloadSceneCommand final : public MoE::Command
{
public:

	ReloadSceneCommand() = default;
	virtual ~ReloadSceneCommand() = default;

	ReloadSceneCommand(const ReloadSceneCommand& other) = delete;
	ReloadSceneCommand(ReloadSceneCommand&& other) noexcept = delete;
	ReloadSceneCommand& operator=(const ReloadSceneCommand& other) = delete;
	ReloadSceneCommand& operator=(ReloadSceneCommand&& other) noexcept = delete;

	void Execute() override
	{
		MoE::SceneManager::Get().ReloadScene();
	}

};

#endif // !RELOADSCENECOMMAND_H