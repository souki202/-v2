#include "JudgeLine.h"
#include "PlaySettings.h"

void JudgeLine::draw()
{
	for (auto& x : judgeIcons) x->draw();
}

void JudgeLine::loadJudgeIcons(int numOfLines)
{
	if (!numOfLines) numOfLines = numLine;
	else setNumLine(numOfLines);
	judgeIcons.clear();
	for (int i = 0; i < numOfLines; i++) {
		judgeIcons.push_back(std::make_unique<Image>("Images/Play/judgePoint.png"));
		judgeIcons.back()->setAlign(Align::Horizontal::CENTER, Align::Vertical::MIDDLE);
		judgeIcons.back()->setPosition(getCenterPosition(i), GET_JUDGE_Y());
	}
}
