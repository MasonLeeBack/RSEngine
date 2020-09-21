/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: Timer.h

*/

#ifndef _TIMER_H_
#define _TIMER_H_

namespace rs {
	class Timer {
	private:
		long long int startTime;
		long long int totalIdleTime;
		long long int pausedTime;
		long long int currentTime;
		long long int previousTime;

		double secondsPerCount;
		double deltaTime;

		bool timerStopped;
	public:
		Timer();

		double getTimeElapsed() const;
		// We point this to the main game tick- objects can reference it from there
		// if needed.
		double getDeltaTime() const;

		void start();
		void reset();
		void tick();
		void stop();
	};

} // namespace rs

#endif // _TIMER_H_
