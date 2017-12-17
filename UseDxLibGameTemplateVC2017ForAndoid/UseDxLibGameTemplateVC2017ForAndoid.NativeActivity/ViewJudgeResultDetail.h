#pragma once
#include "MyFuncs.h"
#include "ViewString.h"
#include "JudgeGrade.h"

class ViewJudgeResultDetail {
public:
	ViewJudgeResultDetail() { largeFont = LoadFontDataToHandle("Font/36px_number.dft"); };
	~ViewJudgeResultDetail() { DeleteFontToHandle(largeFont); };

	void update();
	void draw();
	void setJudgeCount(const std::array<int, static_cast<int>(JudgeGrade::INVALID)>& count,
		               const std::array<int, static_cast<int>(JudgeGrade::INVALID)>& bestCount);
	void setScore(int score, int bestScore, int exScore, int bestExScore);
	void setCombo(int combo, int bestCombo);
	void setFont(int normal, int small);
private:
	int smallFont = 0;
	int normalFont = 0;
	int largeFont = 0; //Ç±ÇÍÇæÇØÇ±Ç±Ç≈ì«Ç›çûÇ›
	std::array<int, static_cast<int>(JudgeGrade::INVALID)> judgeCount;
	std::array<int, static_cast<int>(JudgeGrade::INVALID)> judgeBestCount;
	std::array<ViewString, static_cast<int>(JudgeGrade::INVALID)> judgeCurrentStr;
	std::array<ViewString, static_cast<int>(JudgeGrade::INVALID)> judgeBestStr;
	ViewString comboStr[2];
	std::array<ViewString, 4> scoreStr;
	static constexpr int DRAW_INTERVAL = 46;
	static constexpr float BASE_X = 390.f;
	static constexpr float BASE_BEST_X = BASE_X + 150.f;
};