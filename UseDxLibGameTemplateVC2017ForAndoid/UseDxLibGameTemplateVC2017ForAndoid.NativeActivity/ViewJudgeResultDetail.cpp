#include "ViewJudgeResultDetail.h"

void ViewJudgeResultDetail::update()
{
}

void ViewJudgeResultDetail::draw()
{
	for (auto& x : judgeCurrentStr) x.draw();
	for (auto& x : judgeBestStr) x.draw();
	for (auto& x : scoreStr) x.draw();
	for (auto& x : comboStr) x.draw();
}

void ViewJudgeResultDetail::setJudgeCount(const std::array<int, static_cast<int>(JudgeGrade::INVALID)>& count,
	                                const std::array<int, static_cast<int>(JudgeGrade::INVALID)>& bestCount)
{
	judgeCount = count;
	judgeBestCount = bestCount;
	for (int i = 0; i < static_cast<int>(judgeCurrentStr.size()); i++) {
		judgeCurrentStr[i].setString(MyFuncs::to_string(judgeCount[i]));
		judgeCurrentStr[i].setAlign(Align::Horizontal::RIGHT, Align::Vertical::BOTTOM);
		judgeCurrentStr[i].setPosition(BASE_X, 290.f + i * DRAW_INTERVAL);
		judgeCurrentStr[i].setColor(0x414141);
	}
	for (int i = 0; i < static_cast<int>(judgeBestStr.size()); i++) {
		judgeBestStr[i].setString(MyFuncs::to_string(judgeBestCount[i]));
		judgeBestStr[i].setAlign(Align::Horizontal::RIGHT, Align::Vertical::BOTTOM);
		judgeBestStr[i].setPosition(BASE_BEST_X, 290.f + i * DRAW_INTERVAL);
		judgeBestStr[i].setColor(0x414141);
	}
}

void ViewJudgeResultDetail::setScore(int score, int bestScore, int exScore, int bestExScore)
{
	scoreStr[0].setString(MyFuncs::to_string(score));
	scoreStr[1].setString(MyFuncs::to_string(bestScore));
	scoreStr[2].setString(MyFuncs::to_string(exScore));
	scoreStr[3].setString(MyFuncs::to_string(bestExScore));
	for (auto& x : scoreStr) x.setAlign(Align::Horizontal::RIGHT, Align::Vertical::BOTTOM);
	for (int i = 0; i < 4; i ++) {
		if (i % 2 == 0) scoreStr[i].setFont(largeFont);
		else scoreStr[i].setFont(smallFont);
		scoreStr[i].setColor(0x414141);
	}
	scoreStr[0].setPosition(BASE_X, 625.f);
	scoreStr[1].setPosition(BASE_BEST_X, 625.f);
	scoreStr[2].setPosition(BASE_X, 680.f);
	scoreStr[3].setPosition(BASE_BEST_X, 680.f);
}

void ViewJudgeResultDetail::setCombo(int combo, int bestCombo)
{
	comboStr[0].setString(MyFuncs::to_string(combo));
	comboStr[1].setString(MyFuncs::to_string(bestCombo));
	comboStr[0].setPosition(BASE_X, 545.f);
	comboStr[1].setPosition(BASE_BEST_X, 545.f);
	for (auto& x : comboStr) {
		x.setColor(0x414141);
		x.setAlign(Align::Horizontal::RIGHT, Align::Vertical::BOTTOM);
	}
}

void ViewJudgeResultDetail::setFont(int normal, int small)
{
	normalFont = normal;
	smallFont = small;
	for (auto& x : judgeCurrentStr) {
		x.setFont(normal);
	}
	for (auto& x : judgeBestStr) {
		x.setFont(small);
	}
	for (int i = 0; i < 4; i++) {
		if (i % 2 == 0) scoreStr[i].setFont(largeFont);
		else scoreStr[i].setFont(smallFont);
	}
	comboStr[0].setFont(normal);
	comboStr[1].setFont(small);
}
