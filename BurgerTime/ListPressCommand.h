#ifndef LISTPRESSCOMMAND_H
#define LISTPRESSCOMMAND_H

#include "Command.h"
#include "ListSelection.h"

class ListPressCommand final : public MoE::Command
{
public:

	explicit ListPressCommand(ListSelection* const list)
		: m_pList{ list }
	{
	}
	virtual ~ListPressCommand() = default;

	ListPressCommand(const ListPressCommand& other) = delete;
	ListPressCommand(ListPressCommand&& other) noexcept = delete;
	ListPressCommand& operator=(const ListPressCommand& other) = delete;
	ListPressCommand& operator=(ListPressCommand&& other) noexcept = delete;

	virtual void Execute() override
	{
		if (m_pList) m_pList->Press();
	}

private:

	ListSelection* m_pList;

};

#endif // !LISTPRESSCOMMAND_H
