#ifndef INFOMENU_H
#define INFOMENU_H

#include "Component.h"

namespace MoE
{
	class GameObject;
}

class InfoMenu final : public MoE::Component
{
public:

	explicit InfoMenu(MoE::GameObject* const owner);
	virtual ~InfoMenu() = default;

	InfoMenu(const InfoMenu& other) = delete;
	InfoMenu(InfoMenu&& other) noexcept = delete;
	InfoMenu& operator=(const InfoMenu& other) = delete;
	InfoMenu& operator=(InfoMenu&& other) noexcept = delete;

	virtual void SceneStart() override;
	virtual void Update() override;

private:

	float m_CurrentWaitTime;
	float m_TotalWaitTime;

};

#endif // !INFOMENU_H