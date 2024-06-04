#include "Button.h"
#include "TextureRenderer.h"
#include "GameObject.h"
#include "GameManager.h"

Button::Button(MoE::GameObject* const owner, SharedTexture buttonTexture)
	: Button{ owner, buttonTexture, nullptr }
{
}

Button::Button(MoE::GameObject* const owner, SharedTexture buttonTexture, SharedTexture buttonSelectedTexture)
	: Component{ owner }
	, m_pRenderComp{}
	, m_IsSelected{}
	, m_ButtonTexture{ buttonTexture }
	, m_SelectedTexture{ buttonSelectedTexture }
{
}

Button::~Button() = default;

void Button::SceneStart()
{
	if (MoE::TextureRenderer* renderComp{ GetOwner()->GetComponent<MoE::TextureRenderer>() }; renderComp)
	{
		m_pRenderComp = renderComp;
	}
}

void Button::Press()
{
	if (!m_IsSelected) return;
}

void Button::Select()
{
	m_IsSelected = true;
	UpdateButtonTexture();
}

void Button::UnSelect()
{
	m_IsSelected = false;
	UpdateButtonTexture();
}

void Button::UpdateButtonTexture()
{
	if (!m_pRenderComp) return;

	const SharedTexture rightTexture{ m_IsSelected ? m_SelectedTexture : m_ButtonTexture };
	if (rightTexture) m_pRenderComp->SetTexture(rightTexture);
}