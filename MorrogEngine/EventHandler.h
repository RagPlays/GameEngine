#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

namespace MoE
{
	using EventID = int;

	class EventHandler
	{
	public:

		EventHandler() = default;
		virtual ~EventHandler() = default;

		EventHandler(const EventHandler& other) = delete;
		EventHandler(EventHandler&& other) noexcept = delete;
		EventHandler& operator=(const EventHandler& other) = delete;
		EventHandler& operator=(EventHandler&& other) noexcept = delete;

		virtual void HandleEvent(EventID) const = 0;

	};

	class NullEventHandler final : public EventHandler
	{
	public:

		NullEventHandler() = default;
		virtual ~NullEventHandler() = default;

		NullEventHandler(const NullEventHandler& other) = delete;
		NullEventHandler(NullEventHandler&& other) noexcept = delete;
		NullEventHandler& operator=(const NullEventHandler& other) = delete;
		NullEventHandler& operator=(NullEventHandler&& other) noexcept = delete;

		virtual void HandleEvent(EventID) const override {}

	};
}

#endif // !EVENTHANDLER_H