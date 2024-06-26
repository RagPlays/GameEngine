#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include <vector>
#include <array>
#include <memory>

#include "Singleton.h"

namespace MoE
{
	using EventID = int;

	class NullEventHandler;
	class EventHandler;

	class EventQueue final : public Singleton<EventQueue>
	{
	public:

		virtual ~EventQueue();

		EventQueue(const EventQueue& other) = delete;
		EventQueue(EventQueue&& other) noexcept = delete;
		EventQueue& operator=(const EventQueue& other) = delete;
		EventQueue& operator=(EventQueue&& other) noexcept = delete;

		void AddHandler(std::unique_ptr<EventHandler>&& handler);
		void ClearHandlers();
		void AddEvent(EventID eventID);
		void ClearEvents();
		void Update();

	private:

		friend class MoE::Singleton<EventQueue>;
		EventQueue();

	private:

		static constexpr unsigned int s_MaxPending{ 10 };
		unsigned int m_Head;
		unsigned int m_Tail;

		std::vector<std::unique_ptr<EventHandler>> m_Handlers;
		std::array<EventID, s_MaxPending> m_Events;

	};
}

#endif // !EVENTQUEUE_H