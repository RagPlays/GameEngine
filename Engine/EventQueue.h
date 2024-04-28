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

	void SetHandler(std::unique_ptr<EventHandler> handler);
	void AddEvent(GameEvent gameEvent);
	void Update();

private:

	friend class Singleton<EventQueue>;
	EventQueue();

private:

	unsigned int m_Head;
	unsigned int m_Tail;
	static constexpr unsigned int m_MaxPending{ 100 };

	std::unique_ptr<EventHandler> m_Handler;

	std::queue<GameEvent> m_Events;
	//std::array<GameEvent, m_MaxPending> m_Events;
};


#endif // !EVENTQUEUE_H