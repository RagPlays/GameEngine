#ifndef BURGERPART_H
#define BURGERPART_H

#include <memory>

namespace MoE
{
	class Texture2D;
}

class BurgerPart final
{
public:

	void Render() const;

private:

	// Texture
	std::shared_ptr<MoE::Texture2D> m_Texture;

	// 

};

#endif // !BURGERPART_H