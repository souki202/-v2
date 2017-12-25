#include "Note.h"

void Note::update()
{
	p = getViewPercentage();
	//画面外は適当
	if (p < 0 || p > 2) p = 0;
	pos.first = getX(p);
	pos.second = getY(p);
	//セット
	noteImg.setPosition(pos.first, pos.second);
	noteImg.setScale(p, p);

	bomb.update();
}

void Note::draw()
{
	if (!(wasJudged || (p <= 0 || p > 1.3))) {
		noteImg.draw();
	}
	if (wasJudged) bomb.draw();
}

void Note::drawSameTimeNoteLine()
{
	if (!(wasJudged || (p <= 0 || p > 1.3))) {
		//同時押しの接続線の描画. 一方通行
		for (auto& other : sameTimeNotes) {
			auto&& lockOther = other.lock();
			if (lockOther) {
				if (!lockOther->getWasJudged() && lockOther->getTarget() >= target) {
					DrawModiGraphF(getX(), getY() - CONNECT_LINE_HEIGHT / 2.f,
						lockOther->getX(), getY() - CONNECT_LINE_HEIGHT / 2.f,
						lockOther->getX(), getY() + CONNECT_LINE_HEIGHT / 2.f,
						getX(), getY() + CONNECT_LINE_HEIGHT / 2.f,
						noteImageManager.getConnectImage(), true);
				}
			}
		}
	}
}

void Note::setting(int target, float appear, int judgeTime, int uid, int id)
{
	this->target = target;
	this->appearPos = appear;
	this->judgeTime = judgeTime;
	this->id = id;
	this->uid = uid;
}

float Note::getX(float p)
{
	//画面外は適当
	if (p < 0) {
		return INFINITY;
	}

	//x座標
	int appearX = judgeLine.getCenterPosition(appearPos);
	int targetX = judgeLine.getCenterPosition(target);
	float x = appearX + p * (targetX - appearX);

	return x;
}

float Note::getY(float p)
{
	//画面外は適当
	if (p < 0) {
		return INFINITY;
	}

	//y座標
	int yLen = judgeLine.GET_JUDGE_Y() - judgeLine.GET_APPEAR_Y();
	float y = yLen * std::pow(p * 1.2f - 0.2f, 2) + judgeLine.GET_APPEAR_Y();

	return y;
}

float Note::getViewPercentage()
{
	//判定時刻と出現時刻から進行度合いを計算
	int appearTime = judgeTime - playSettings.getViewNoteTime();
	int deltaTime = nowTime - appearTime;
	return static_cast<float>(deltaTime) / playSettings.getViewNoteTime();
}

void Note::setType(NoteType type)
{
	this->type = type;
	noteImg = noteImageManager.getNoteImage(type);
	noteImg.setAlign(Align::Horizontal::CENTER, Align::Vertical::MIDDLE);
}

void Note::setJudge(const JudgeResult & judgeResult)
{
	if (judgeResult.grade != JudgeGrade::INVALID) {
		wasJudged = true;
		touchId = judgeResult.id;
	}
	if (judgeResult.grade <= JudgeGrade::GREAT) {
		bomb.startBomb(target);
	}
}
