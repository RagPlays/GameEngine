#include "Button.h"
#include "TextureRenderer.h"
#include "GameObject.h"
#include "GameManager.h"

Button::Button(MoE::GameObject* const owner, std::function<void()>&& pressFunc)
	: Component{ owner }
	, m_PressFunction{ std::move(pressFunc) }
	, m_DefaultDimentions{}
	, m_IsSelected{}
{
}

void Button::Press()
{
	if (!m_IsSelected) return;

	m_PressFunction();
}

void Button::Select()
{
	m_IsSelected = true;
}

void Button::UnSelect()
{
	m_IsSelected = false;
}