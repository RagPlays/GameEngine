#ifndef TIME_H
#define TIME_H

#include <chrono>

#include "Singleton.h"

namespace MoE
{
	class Timer final : public Singleton<Timer>
	{
	public:

		virtual ~Timer() = default;

		Timer(const Timer& other) = delete;
		Timer(Timer&& other) noexcept = delete;
		Timer& operator=(const Timer& other) = delete;
		Timer& operator=(Timer&& other) noexcept = delete;

		// Update
		void Update();
		void UpdateFpsCap();

		// Getters
		float GetElapsedSec() const;
		float GetFixedElapsedSec() const;
		float GetFPS() const;
		bool GetNeedFixedUpdate();

		// Setters
		void EnableFpsCap(int newFps);
		void DisableFpsCap();
		void EnableVSync();
		void DisableVSync();

	private:

		friend class MoE::Singleton<Timer>;
		Timer();

	private:

		const float m_FixedTimeStep;
		int m_MonitorRefreshRate;
		int m_MillSecPerFrame;
		float m_Lag;
		float m_ElapsedSec;

		bool m_VSync;
		bool m_FpsCapped;

		std::chrono::high_resolution_clock::time_point m_LastTime;

	};
}

#endif // !TIME_H