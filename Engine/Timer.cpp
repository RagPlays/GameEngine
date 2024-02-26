#include <SDL.h>
#include <iostream>
#include <thread>
#include "Timer.h"

Timer::Timer()
	: m_FixedTimeStep{ 0.02f }
	, m_ElapsedSec{}
	, m_Lag{}
	, m_LastTime{ std::chrono::high_resolution_clock::now() }
	, m_FpsCapped{ true }
	, m_MsPerFrame{ 16.67 }
	, m_ShowDebugFps{ false }
	, m_DebugPrintTime{}
	, m_FpsCount{}
{
	SDL_DisplayMode displayMode{};
	SDL_GetCurrentDisplayMode(0, &displayMode);
	std::cout << "Monitor RefreshRate: " << displayMode.refresh_rate << "\n";

	if (m_FpsCapped)
	{
		SetFpsCap(displayMode.refresh_rate);
	}
}

void Timer::Update()
{
	m_CurrentTime = std::chrono::high_resolution_clock::now();
	m_ElapsedSec = std::chrono::duration<float>(m_CurrentTime - m_LastTime).count();
	m_LastTime = m_CurrentTime;
	m_Lag += m_ElapsedSec;

	// DEBUG
	if (m_ShowDebugFps)
	{
		m_DebugPrintTime += m_ElapsedSec;
		++m_FpsCount;

		if (m_DebugPrintTime >= 1.0f)
		{
			std::cout << "FPS: " << static_cast<int>(m_FpsCount / m_DebugPrintTime) << "\n";
			m_DebugPrintTime -= 1.f;
			m_FpsCount = 0;
		}
	}
}

void Timer::CapFps()
{
	if (!m_FpsCapped) return;

	std::chrono::nanoseconds sleepTime{ std::chrono::duration_cast<std::chrono::nanoseconds>(m_CurrentTime + m_MsPerFrame - std::chrono::high_resolution_clock::now()) };
	if (sleepTime > std::chrono::nanoseconds::zero())
	{
		std::this_thread::sleep_for(sleepTime);
	}
}

float Timer::GetElapsedSec()
{
	return m_ElapsedSec;
}

float Timer::GetFixedElapsedSec()
{
	return m_FixedTimeStep;
}

int Timer::GetFPS()
{
	return static_cast<int>(1.f / m_ElapsedSec);
}

float Timer::GetPreciseFPS()
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

void Timer::ClearFpsCap()
{
	m_FpsCapped = false;
}

void Timer::SetFpsCap(int newFps)
{
	m_FpsCapped = true;
	m_MsPerFrame = std::chrono::duration<double, std::milli>(1000.f / newFps);
}