#include "JudgeView.h"

JudgeView::JudgeView()
{
	judgeRawImg = new int[static_cast<int>(JudgeGrade::INVALID)];
	LoadDivGraph("Images/Play/judge.png", 5, 1, 5, 256, 350/5, judgeRawImg);
	for (int i = 0; i < static_cast<int>(JudgeGrade::INVALID); i++) {
		judgeImg[i].setImage(judgeRawImg[i]);
		judgeImg[i].setPosition(CommonSettings::WINDOW_WIDTH / 2, 400);
		judgeImg[i].setAlign(Align::Horizontal::CENTER, Align::Vertical::MIDDLE);
	}
}

JudgeView::~JudgeView()
{
	for (int i = 0; i < static_cast<int>(JudgeGrade::INVALID); i++) {
		DeleteGraph(i);
	}
	if (judgeRawImg != nullptr) {
		delete[] judgeRawImg;
		judgeRawImg = nullptr;
	}
}

void JudgeView::setGrade(const JudgeGrade & grade)
{
	if (grade != JudgeGrade::INVALID) {
		nowJudgeViewTime.reset();
		this->grade = grade;
		judgeImg[static_cast<int>(grade)].setScale(0.f, 0.f);
	}
}

void JudgeView::draw()
{
	if (grade != JudgeGrade::INVALID) {
		if (nowJudgeViewTime.getElapsedTime() < viewJudgeTime) {
			judgeImg[static_cast<int>(grade)].draw();
		}
	}
}

void JudgeView::update()
{
	if (grade != JudgeGrade::INVALID) {
		nowJudgeViewTime.update();
		float scale = 0.5f + nowJudgeViewTime.getElapsedTime() / 200.f;
		scale = std::min(scale, 1.f);
		judgeImg[static_cast<int>(grade)].setScale(scale, scale);
	}
}
