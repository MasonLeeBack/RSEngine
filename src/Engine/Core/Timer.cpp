/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: Timer.cpp

*/

#include <Windows.h>
#include <Core/Timer.h>

namespace rs {
	Timer::Timer() : startTime(0), totalIdleTime(0), pausedTime(0), currentTime(0), previousTime(0),
		secondsPerCount(0.0), deltaTime(0.0), timerStopped(false)
	{
		long long int frequency = 0;
		if (QueryPerformanceCounter((LARGE_INTEGER*)&frequency)) {
			secondsPerCount = 1.0 / (double)frequency;
		}
		else {
			// We will update this for Linux platforms and macOS later on
		}
	}

	double Timer::getTimeElapsed() const
	{
		if (timerStopped == true)
			return (pausedTime - startTime - totalIdleTime) * secondsPerCount;
		else
			return (currentTime - startTime - totalIdleTime) * secondsPerCount;
	}

	double Timer::getDeltaTime() const
	{
		return deltaTime;
	}

	void Timer::start()
	{
		if (timerStopped == true) {
			long long int now = 0;
			if (QueryPerformanceCounter((LARGE_INTEGER*)&now)) {
				totalIdleTime += (now - pausedTime);
				previousTime = now;
				pausedTime = 0;
				timerStopped = false;
				return;
			}
			else {
				// Linux fallback
				return;
			}
		}
		return;
	}

	void Timer::reset()
	{
		long long int now = 0;
		if (QueryPerformanceCounter((LARGE_INTEGER*)&now))
		{
			startTime = now;
			previousTime = now;
			pausedTime = 0;
			timerStopped = false;

			// return success
			return;
		}
		else {
			// Linux support
			return;
		}
		return;
	}

	void Timer::tick()
	{
		// this function lets the timer tick, i.e. it computes the time that has elapsed between two frames
		if (timerStopped == true)
		{
			// if the game is stopped, the elapsed time is obviously 0
			deltaTime = 0.0;

			// return success
			return;
		}
		else
		{
			// get the current time
			if (QueryPerformanceCounter((LARGE_INTEGER*)&currentTime))
			{
				// compute the time elapsed since the previous frame
				deltaTime = (currentTime - previousTime) * secondsPerCount;

				// set previousTime to crrentTime, as in the next tick, this frame will be the previous frame
				previousTime = currentTime;

				// deltaTime can be negative if the processor goes idle for example
				if (deltaTime < 0.0)
					deltaTime = 0.0;

				// return success
				return;
			}
			else {
				// Linux shit
				return;
			}
		}
		return;
	}

	void Timer::stop()
	{
		if (timerStopped == false) {
			long long int now = 0;
			if (QueryPerformanceCounter((LARGE_INTEGER*)&now)) {
				pausedTime = now;
				timerStopped = true;
				return;
			}
			else {
				return;
			}
		}
		return;
	}

} // namespace rs
