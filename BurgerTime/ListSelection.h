#ifndef LISTSELECTION_H
#define LISTSELECTION_H

#include <vector>
#include <memory>

#include "Component.h"

namespace MoE
{
	class GameObject;
}

class Button;

class ListSelection final : public MoE::Component
{
public:

	explicit ListSelection(MoE::GameObject* const owner, bool looping);

	virtual ~ListSelection();

	ListSelection(const ListSelection& other) = delete;
	ListSelection(ListSelection&& other) noexcept = delete;
	ListSelection& operator=(const ListSelection& other) = delete;
	ListSelection& operator=(ListSelection&& other) noexcept = delete;

	void AddButton(std::unique_ptr<Button>&& button);

	void MoveUp();
	void MoveDown();

	void SetLooping(bool looping);

private:

	bool m_Looping;
	int m_SelectedIndex;

	//std::vector<std::unique_ptr<Button>> m_Buttons;

};

#endif // !LISTSELECTION_H