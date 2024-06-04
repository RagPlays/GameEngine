#ifndef BUTTON_H
#define BUTTON_H

#include <memory>

#include "Component.h"

namespace MoE
{
	class Texture2D;
	class GameObject;
	class TextureRenderer;
}

using SharedTexture = std::shared_ptr<MoE::Texture2D>;

class Button final : public MoE::Component
{ 
	explicit Button(MoE::GameObject* const owner, SharedTexture buttonTexture);
	explicit Button(MoE::GameObject* const owner, SharedTexture buttonTexture, SharedTexture buttonSelectedTexture);

	virtual ~Button();

	Button(const Button& other) = delete;
	Button(Button&& other) noexcept = delete;
	Button& operator=(const Button& other) = delete;
	Button& operator=(Button&& other) noexcept = delete;

	virtual void SceneStart() override;

	void Press();

	void Select();
	void UnSelect();

private:

	void UpdateButtonTexture();

private:
	
	MoE::TextureRenderer* m_pRenderComp;
	bool m_IsSelected;
	std::shared_ptr<MoE::Texture2D> m_ButtonTexture;
	std::shared_ptr<MoE::Texture2D> m_SelectedTexture;

};

#endif // !BUTTON_H
