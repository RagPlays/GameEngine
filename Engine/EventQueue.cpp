#include <cassert>
#include "EventQueue.h"
#include "EventHandler.h"

EventQueue::~EventQueue() = default;

void EventQueue::AddHandler(std::unique_ptr<EventHandler>&& handler)
{
	m_Handlers.emplace_back(std::move(handler));
	if (m_Handlers.size() == 1) m_NullEventHandler.reset();
}

void EventQueue::AddEvent(GameEvent gameEvent)
{
	assert((m_Tail + 1) % s_MaxPending != m_Head);
	if ((m_Tail + 1) % s_MaxPending == m_Head) return;

	m_Events[m_Tail] = gameEvent;
	m_Tail = (m_Tail + 1) % s_MaxPending;
}

void EventQueue::ClearEvents()
{
	m_Head = m_Tail;
}

void EventQueue::Update()
{
	if (m_Handlers.empty()) return;

	for (unsigned int idx{ m_Head }; idx != m_Tail; idx = (idx + 1) % s_MaxPending)
	{
		for (const auto& handler : m_Handlers)
		{
			handler->HandleEvent(m_Events[idx]);
		}
	}
	m_Head = m_Tail;
}

// PRIVATE FUNCTIONS //

EventQueue::EventQueue()
	: m_NullEventHandler{ nullptr }
	, m_Head{ 0 }
	, m_Tail{ 0 }
	, m_Events{}
{
	m_NullEventHandler = std::make_unique<NullEventHandler>();
}