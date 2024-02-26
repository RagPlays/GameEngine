#include <SDL.h>
#include <iostream>
#include <thread>
#include "Timer.h"

Timer::Timer()
	: m_FixedTimeStep{ 0.02f }
	, m_ElapsedSec{}
	, m_FPS{}
	, m_Lag{}
	, m_LastTime{ std::chrono::high_resolution_clock::now() }
	, m_FpsCapped{ true }
	, m_MsPerFrame{ 16 }
	, m_ShowDebugFps{ true }
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
	m_FPS = 1.f / m_ElapsedSec;
}

void Timer::CapFps()
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

void Timer::ClearFpsCap()
{
	m_FpsCapped = false;
}

void Timer::SetFpsCap(int newFps)
{
	m_FpsCapped = true;
	m_MsPerFrame = static_cast<int>(1.f / newFps * 1000.f);
}