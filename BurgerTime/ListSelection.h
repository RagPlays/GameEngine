#ifndef LISTSELECTION_H
#define LISTSELECTION_H

#include <vector>
#include <memory>

#include "Component.h"

namespace MoE
{
	class GameObject;
	class Texture2D;
	class TextureRenderer;
}

class Button;

class ListSelection final : public MoE::Component
{
public:

	explicit ListSelection(MoE::GameObject* const owner, bool looping, int offset, std::shared_ptr<MoE::Texture2D> makerTexture, int startButtonPosY);

	virtual ~ListSelection();

	ListSelection(const ListSelection& other) = delete;
	ListSelection(ListSelection&& other) noexcept = delete;
	ListSelection& operator=(const ListSelection& other) = delete;
	ListSelection& operator=(ListSelection&& other) noexcept = delete;

	virtual void SceneStart() override;

	void AddButton(std::unique_ptr<MoE::GameObject>&& button);

	void Press();
	void Move(bool up);

	void ManualSelect(uint8_t idx);
	void SetLooping(bool looping);

private:

	void UpdateMarker();

private:

	MoE::TextureRenderer* m_pMarkerRenderer;
	int m_MarkerOffset;
	int m_StartButtonYPos;

	bool m_Looping;
	int m_SelectedIndex;

	std::vector<Button*> m_pButtons;

};

#endif // !LISTSELECTION_H