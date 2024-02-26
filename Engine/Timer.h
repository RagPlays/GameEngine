#ifndef TIME_H
#define TIME_H

#include <chrono>
#include "Singleton.h"

class Timer final :  public Singleton<Timer>
{
public:
	Timer();
	virtual ~Timer() = default;

	Timer(const Timer& other) = delete;
	Timer(Timer&& other) noexcept = delete;
	Timer& operator=(const Timer& other) = delete;
	Timer& operator=(Timer && other) noexcept = delete;

	// Update
	void Update();
	void CapFps();

	// Getters
	float GetElapsedSec();
	float GetFixedElapsedSec();
	int GetFPS();
	float GetPreciseFPS();
	bool GetNeedFixedUpdate();

	// Setters
	void ClearFpsCap();
	void SetFpsCap(int newFps);

private:
	
	bool m_FpsCapped;
	std::chrono::duration<double, std::milli> m_MsPerFrame;

	const float m_FixedTimeStep;
	float m_ElapsedSec;
	float m_Lag;
	std::chrono::high_resolution_clock::time_point m_CurrentTime;
	std::chrono::high_resolution_clock::time_point m_LastTime;

	// DEBUG
	bool m_ShowDebugFps;
	float m_DebugPrintTime;
	int m_FpsCount;
};

#endif // !TIME_H