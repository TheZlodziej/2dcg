#pragma once
#include <chrono>

class Timer
{
private:
	std::chrono::time_point<std::chrono::system_clock> _currentTime;
	std::chrono::duration<float> _deltaTime;

public:
	Timer();
	void Tick();
	float DeltaTime();
};

