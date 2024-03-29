#ifndef TIME_H
#define TIME_H

#include <SDL.h>
#include <chrono>
#include "Singleton.h"

class Timer final :  public Singleton<Timer>
{
public:
	explicit Timer();
	virtual ~Timer() = default;

	Timer(const Timer& other) = delete;
	Timer(Timer&& other) noexcept = delete;
	Timer& operator=(const Timer& other) = delete;
	Timer& operator=(Timer && other) noexcept = delete;

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

	SDL_DisplayMode m_MonitorInfo;
	
	bool m_VSync;
	bool m_FpsCapped;
	int m_MsPerFrame;

	const float m_FixedTimeStep;
	float m_ElapsedSec;
	float m_FPS;
	float m_Lag;
	std::chrono::high_resolution_clock::time_point m_CurrentTime;
	std::chrono::high_resolution_clock::time_point m_LastTime;
};

#endif // !TIME_H