#include "Timer.h"

Timer::Timer()
{
	_currentTime = std::chrono::system_clock::now();
	_deltaTime = std::chrono::duration<float>(0.0f);
}

void Timer::Tick()
{
	std::chrono::time_point<std::chrono::system_clock> tickTime = std::chrono::system_clock::now();
	_deltaTime = tickTime - _currentTime;
}

float Timer::DeltaTime()
{
	return _deltaTime.count();
}