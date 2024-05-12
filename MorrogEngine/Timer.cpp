#include <thread>
#include <SDL.h>

#include "Timer.h"

namespace MoE
{
	void Timer::Update()
	{
		auto now{ std::chrono::high_resolution_clock::now() };
		m_ElapsedSec = std::chrono::duration<float>(now - m_LastTime).count();
		m_LastTime = now;
		m_Lag += m_ElapsedSec;
	}

	void Timer::UpdateFpsCap()
	{
		if (!m_FpsCapped) return;

		const auto sleeptime{ m_LastTime + std::chrono::milliseconds(m_MsPerFrame) - std::chrono::high_resolution_clock::now() };
		if (sleeptime > std::chrono::nanoseconds::zero())
		{
			std::this_thread::sleep_for(sleeptime); // main thread
		}
	}

	float Timer::GetElapsedSec() const
	{
		return m_ElapsedSec;
	}

	float Timer::GetFixedElapsedSec() const
	{
		return m_FixedTimeStep;
	}

	float Timer::GetFPS() const
	{
		return 1.f / m_ElapsedSec;
	}

	bool Timer::GetNeedFixedUpdate()
	{
		if (m_Lag >= m_FixedTimeStep)
		{
			m_Lag -= m_FixedTimeStep;
			return true;
		}
		return false;
	}

	void Timer::EnableFpsCap(int newFps)
	{
		m_FpsCapped = true;
		m_MsPerFrame = static_cast<int>(1.f / newFps * 1000.f);
	}

	void Timer::DisableFpsCap()
	{
		DisableVSync();
		m_FpsCapped = false;
	}

	void Timer::EnableVSync()
	{
		// Only works when Graphics Card supports VSync and is not set off.
		if (!m_VSync)
		{
			m_VSync = true;
			SDL_GL_SetSwapInterval(1);
		}
	}

	void Timer::DisableVSync()
	{
		if (m_VSync)
		{
			m_VSync = false;
			SDL_GL_SetSwapInterval(0);
		}
	}

	// Private Functions //
	Timer::Timer()
		: m_VSync{ false }
		, m_FixedTimeStep{ 0.02f }
		, m_ElapsedSec{}
		, m_Lag{}
		, m_FpsCapped{ false }
		, m_MsPerFrame{ 16 }
		, m_LastTime{ std::chrono::high_resolution_clock::now() }
	{
		SDL_DisplayMode monitorInfo{};
		SDL_GetCurrentDisplayMode(0, &monitorInfo);
		m_MonitorRefreshRate = monitorInfo.refresh_rate;

		if (m_VSync)
		{
			SDL_GL_SetSwapInterval(1);
		}
		else if (m_FpsCapped)
		{
			EnableFpsCap(m_MonitorRefreshRate);
		}
	}
}