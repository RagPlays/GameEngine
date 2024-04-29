#include <thread>
#include "Timer.h"

void Timer::Update()
{
	m_CurrentTime = std::chrono::high_resolution_clock::now();
	m_ElapsedSec = std::chrono::duration<float>(m_CurrentTime - m_LastTime).count();
	m_LastTime = m_CurrentTime;
	m_Lag += m_ElapsedSec;
	m_FPS = 1.f / m_ElapsedSec;
}

void Timer::UpdateFpsCap()
{
	if (!m_FpsCapped) return;

	const auto sleeptime{ m_CurrentTime + std::chrono::milliseconds(m_MsPerFrame) - std::chrono::high_resolution_clock::now() };
	if (sleeptime > std::chrono::nanoseconds::zero())
	{
		std::this_thread::sleep_for(sleeptime);
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
	return m_FPS;
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
	, m_FPS{}
	, m_Lag{}
	, m_LastTime{ std::chrono::high_resolution_clock::now() }
	, m_FpsCapped{ false }
	, m_MsPerFrame{ 16 }
{
	SDL_GetCurrentDisplayMode(0, &m_MonitorInfo);

	if (m_VSync)
	{
		SDL_GL_SetSwapInterval(1);
	}
	else if (m_FpsCapped)
	{
		EnableFpsCap(m_MonitorInfo.refresh_rate);
	}
}