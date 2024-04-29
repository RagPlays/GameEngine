#include <cassert>
#include "EventQueue.h"

void EventQueue::SetHandler(std::unique_ptr<EventHandler>&& handler)
{
	m_Handler.reset();
	m_Handler = std::move(handler);
}

void EventQueue::AddEvent(GameEvent gameEvent)
{
	assert((m_Tail + 1) % s_MaxPending != m_Head);
	if ((m_Tail + 1) % s_MaxPending == m_Head) return;

	m_Events[m_Tail] = gameEvent;
	m_Tail = (m_Tail + 1) % s_MaxPending;
}

void EventQueue::Update()
{
	if (!m_Handler.get()) return;

	for (unsigned int idx{ m_Head }; idx != m_Tail; idx = (idx + 1) % s_MaxPending)
	{
		m_Handler->HandleEvent(m_Events[idx]);
	}
	m_Head = m_Tail;
}

// PRIVATE FUNCTIONS //

EventQueue::EventQueue()
	: m_Handler{ nullptr }
	, m_Head{ 0 }
	, m_Tail{ 0 }
	, m_Events{}
{
	//m_Handler = std::make_unique<NullEventHandler>();
}