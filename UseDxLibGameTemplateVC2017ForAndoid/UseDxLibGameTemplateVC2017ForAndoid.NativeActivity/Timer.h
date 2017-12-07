#pragma once
#include <chrono>

class Timer {
public:
	Timer() {
		reset();
	}
	~Timer() {}

	void update() {
		lastTime = nowTime;
		nowTime = std::chrono::system_clock::now();
	}

	void reset() {
		nowTime = std::chrono::system_clock::now();
		initTime = lastTime = nowTime;
	}

	int getDeltaTime() {
		return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - lastTime).count());
	}

	int getElapsedTime() {
		return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - initTime).count());
	}

private:
	std::chrono::system_clock::time_point nowTime, lastTime, initTime;
};