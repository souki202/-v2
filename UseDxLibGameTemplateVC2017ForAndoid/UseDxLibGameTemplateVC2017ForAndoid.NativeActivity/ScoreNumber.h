#pragma once
#include <array>
#include "Timer.h"
#include "Image.h"
#include "Easing.h"
#include "MyFuncs.h"
#include "Debug.h"

class ScoreNumber {
public:
	ScoreNumber();
	~ScoreNumber() { for (auto& x : numberImg) DeleteGraph(x); };

	void draw();
	void update();

	void setScore(int score) { if (score) { lastScore = nowScore; nowScore = score; timer.reset(); } };
private:
	Timer timer;
	static constexpr float BASE_X = 335.f;
	static constexpr int MAX_DIGITS = 7;
	std::array<Image, MAX_DIGITS> scoreImg;
	int numberImg[10];
	int drawScore = 0;
	int lastScore = 0;
	int nowScore = 0;
};