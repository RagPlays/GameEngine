#ifndef BURGERPART_H
#define BURGERPART_H

#include <memory>

#include "Structs.h"

namespace MoE
{
	struct Recti;
}

namespace MoE
{
	class Texture2D;
}

class BurgerPart final
{
public:

	explicit BurgerPart
	(
		const MoE::Rectf& hitbox,
		std::shared_ptr<MoE::Texture2D> burgerType,
		const MoE::Recti& srcRect
	);
	virtual ~BurgerPart() = default;

	void Render() const;

	bool GetIsPushed() const;

	void CheckForCollision(const MoE::Rectf& hitbox);

private:

	// Texture
	const std::shared_ptr<MoE::Texture2D> m_Texture;
	MoE::Recti m_SrcRect;

	//
	bool m_Pushed;
	float m_PushDistance;
	MoE::Rectf m_Hitbox;

};

#endif // !BURGERPART_H