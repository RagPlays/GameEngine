#ifndef BURGERHOLDER_H
#define BURGERHOLDER_H

#include <vector>

#include "Structs.h"

namespace MoE
{
	struct Linei;
}

class Burger;

class BurgerHolder final
{
public:

	explicit BurgerHolder(int nrOfBurgers, int holdHeight);
	~BurgerHolder() = default;

#if defined DEBUG || _DEBUG
	void Render() const;
#endif

	void AddBurger(Burger* burger);

	void CheckForCollision(const MoE::Recti& hitbox);
	void CheckInHolder();
	void CheckOverLapping(Burger* burger);

	int GetCurrentHoldHeight() const;
	bool IsHolderCompleted() const;

private:

	std::vector<Burger*> m_Burgers;
	int m_CurrentSizeNr;
	const int m_FullSizeNr;
	const int m_BurgerHoldHeight;

};


#endif // !BURGERHOLDER_H
