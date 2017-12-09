#include "Note.h"

void Note::update()
{
	float p = getViewPercentage();
	//画面外は適当
	if (p < 0 || p > 2) p = -1000;
	pos.first = getX(p);
	pos.second = getY(p);
	//セット
	noteImg.setPosition(getX(p), getY(p));
	noteImg.setScale(p, p);
}

void Note::draw()
{
	if (wasJudged) return;
	noteImg.draw();

#ifdef DEBUG
	DrawFormatString(noteImg.getPosition().first, noteImg.getPosition().second, 0xffffff, "UID:%d", uid);
	//DrawFormatString(100, 16 * uid, 0xffffff, "time:%d, uid:%d, type:%d", judgeTime, uid, type);
	//
	////ノート出現中
	//int appearTime = judgeTime - playSettings.getViewNoteTime();
	//int deltaTime = nowTime - appearTime;
	//float p = static_cast<float>(deltaTime) / playSettings.getViewNoteTime();
	//DrawFormatString(400, 16 * uid, 0xffffff, "p:%f", p);
	//if (0 < p && p <= 1) {
	//	DrawFormatString(300, 16*uid, 0xffffff, "出現中");
	//}
#endif
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
	//座標計算
	int viewTime = playSettings.getViewNoteTime();

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
}
