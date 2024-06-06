#ifndef BUTTON_H
#define BUTTON_H

#include <memory>
#include <functional>

#include "Component.h"

namespace MoE
{
	class Texture2D;
	class GameObject;
	class TextureRenderer;
}

class Button final : public MoE::Component
{
public:

	explicit Button(MoE::GameObject* const owner, std::function<void()>&& pressFunc);
	virtual ~Button() = default;

	Button(const Button& other) = delete;
	Button(Button&& other) noexcept = delete;
	Button& operator=(const Button& other) = delete;
	Button& operator=(Button&& other) noexcept = delete;

	void Press();

	void Select();
	void UnSelect();

private:
	
	std::function<void()> m_PressFunction;
	const glm::ivec2 m_DefaultDimentions;
	bool m_IsSelected;

};

#endif // !BUTTON_H
