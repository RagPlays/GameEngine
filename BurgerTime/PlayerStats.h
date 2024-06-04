#ifndef PLAYERSTATSCOMPONENT_H
#define PLAYERSTATSCOMPONENT_H

#include "Component.h"
#include "Observer.h"

using EventID = int;

namespace MoE
{
	class GameObject;
	class Subject;
}

class Player;

class PlayerStats final : public MoE::Component/*, public MoE::Observer*/
{
public:

	explicit PlayerStats(MoE::GameObject* const owner, MoE::Subject* const subject);
	virtual ~PlayerStats() = default;

	PlayerStats(const PlayerStats& other) = delete;
	PlayerStats(PlayerStats&& other) noexcept = delete;
	PlayerStats& operator=(const PlayerStats& other) = delete;
	PlayerStats& operator=(PlayerStats&& other) noexcept = delete;

	void Update() override;

	/*void OnNotify(MoE::GameObject* gameObj, EventID eventID) override;*/

private:

	bool m_NeedsUpdate;
	int m_PlayerIdx;
	int m_Lives;
	int m_Score;

};

#endif // !PLAYERSTATE