#ifndef LISTNAVCOMMAND_H
#define LISTNAVCOMMAND_H

#include "Command.h"
#include "ListSelection.h"

class ListNavCommand final : public MoE::Command
{
public:

	explicit ListNavCommand(ListSelection* const list, bool navUp)
		: m_pList{ list }
		, m_Up{ navUp }
	{
	}
	virtual ~ListNavCommand() = default;

	ListNavCommand(const ListNavCommand& other) = delete;
	ListNavCommand(ListNavCommand&& other) noexcept = delete;
	ListNavCommand& operator=(const ListNavCommand& other) = delete;
	ListNavCommand& operator=(ListNavCommand&& other) noexcept = delete;

	void Execute() override
	{
		if(m_pList) m_pList->Move(m_Up);
	}

private:

	ListSelection* const m_pList;
	bool m_Up;

};

#endif // !LISTNAVCOMMAND_H
