#ifndef OBSERVER_H
#define OBSERVER_H

namespace MoE
{
	class GameObject;
	class Subject;
	enum class GameEvent;

	class Observer
	{
	public:

		virtual ~Observer();

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) noexcept = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) noexcept = delete;

		virtual void OnNotify(GameObject* gameObj, GameEvent event) = 0;

	protected:

		Observer(Subject* const subject);

	private:

		Subject* const m_pSubject;

	};
}

#endif // !OBSERVER_H