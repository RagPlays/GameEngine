#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <array>
#include <queue>
#include <memory>

#include "Singleton.h"
#include "GameEvents.h"
#include "EventHandler.h"

class EventQueue final : public Singleton<EventQueue>
{
public:

	virtual ~EventQueue() = default;

	EventQueue(const EventQueue& other) = delete;
	EventQueue(EventQueue&& other) noexcept = delete;
	EventQueue& operator=(const EventQueue& other) = delete;
	EventQueue& operator=(EventQueue&& other) noexcept = delete;

	void AddHandler(std::unique_ptr<EventHandler>&& handler);
	void AddEvent(GameEvent gameEvent);
	void ClearEvents();
	void Update();

private:

	friend class Singleton<EventQueue>;
	EventQueue();

private:

	static constexpr unsigned int s_MaxPending{ 10 };
	unsigned int m_Head;
	unsigned int m_Tail;

	std::unique_ptr<NullEventHandler> m_NullEventHandler;
	std::vector<std::unique_ptr<EventHandler>> m_Handlers;

	std::array<GameEvent, s_MaxPending> m_Events;
};


#endif // !EVENTQUEUE_H