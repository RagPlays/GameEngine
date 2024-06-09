#ifndef INFOMENU_H
#define INFOMENU_H

#include "Component.h"

namespace MoE
{
	class GameObject;
}

class WaitMenu final : public MoE::Component
{
public:

	explicit WaitMenu(MoE::GameObject* const owner, float waitTime = 3.f, bool startMenu = false);
	virtual ~WaitMenu() = default;

	WaitMenu(const WaitMenu& other) = delete;
	WaitMenu(WaitMenu&& other) noexcept = delete;
	WaitMenu& operator=(const WaitMenu& other) = delete;
	WaitMenu& operator=(WaitMenu&& other) noexcept = delete;

	virtual void SceneStart() override;
	virtual void Update() override;

private:

	float m_CurrentWaitTime;
	float m_TotalWaitTime;
	bool m_StartMenu;

};

#endif // !INFOMENU_H