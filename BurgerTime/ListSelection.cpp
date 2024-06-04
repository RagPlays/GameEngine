#include "ListSelection.h"
#include "Button.h"

ListSelection::ListSelection(MoE::GameObject* const owner, bool looping)
	: Component{ owner }
	, m_Looping{ looping }
	, m_SelectedIndex{}
{
}

ListSelection::~ListSelection() = default;

void ListSelection::AddButton(std::unique_ptr<Button>&& button)
{
	m_Buttons.emplace_back(std::move(button));
}

void ListSelection::MoveUp()
{
	const int nowSelected{ m_SelectedIndex };
	if (m_Looping)
	{

	}
	else
	{

	}

	if (nowSelected != m_SelectedIndex)
	{

	}
}

void ListSelection::MoveDown()
{
	const int nowSelected{ m_SelectedIndex };
	if (m_Looping)
	{

	}
	else
	{

	}
	if (nowSelected != m_SelectedIndex)
	{
		//m_Buttons[nowSelected]->Update();
	}
}

void ListSelection::SetLooping(bool looping)
{
	m_Looping = looping;
}