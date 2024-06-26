#ifndef STATE_H
#define STATE_H

namespace MoE
{
	class State
	{
	public:

		virtual ~State() = default;

		State(const State& other) = delete;
		State(State&& other) noexcept = delete;
		State& operator=(const State& other) = delete;
		State& operator=(State&& other) noexcept = delete;

		virtual void SceneStart() = 0;
		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void LateUpdate() = 0;

	protected:

		State() = default;

	};
}

#endif // !STATE_H