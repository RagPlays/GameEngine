#include <cassert>
#include "EventQueue.h"

void EventQueue::SetHandler(std::unique_ptr<EventHandler> handler)
{
	m_Handler.reset();
	m_Handler = std::move(handler);
}

void EventQueue::AddEvent(GameEvent gameEvent)
{
	m_Events.push(gameEvent);

	//assert((m_Tail + 1) % m_MaxPending != m_Head);

	//// Add to the end of the list.
	//m_Events[m_Tail] = gameEvent;
	//m_Tail = (m_Tail + 1) % m_MaxPending;
}

void EventQueue::Update()
{
	if (!m_Handler.get()) return;

	while (!m_Events.empty())
	{
		m_Handler->HandleEvent(m_Events.front());
		m_Events.pop();
	}

	/*for (unsigned int idx{ m_Head }; idx != m_Tail; idx = (idx + 1) % m_MaxPending)
	{

	}*/
}

// PRIVATE FUNCTIONS //

EventQueue::EventQueue()
	: m_Handler{ nullptr }
	, m_Head{ 0 }
	, m_Tail{ 0 }
	, m_Events{}
{
}