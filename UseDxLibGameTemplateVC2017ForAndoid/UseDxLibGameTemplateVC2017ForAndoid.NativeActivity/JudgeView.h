#pragma once
#include <array>
#include "Image.h"
#include "Timer.h"
#include "JudgeGrade.h"

class JudgeView {
public:
	JudgeView();
	~JudgeView();

	void setGrade(const JudgeGrade& grade);

	void draw();
	void update();
private:
	JudgeGrade grade = JudgeGrade::INVALID;
	Timer nowJudgeViewTime;
	int viewJudgeTime = 1000;

	int* judgeRawImg = nullptr;
	std::array<Image, static_cast<int>(JudgeGrade::INVALID)> judgeImg;
};