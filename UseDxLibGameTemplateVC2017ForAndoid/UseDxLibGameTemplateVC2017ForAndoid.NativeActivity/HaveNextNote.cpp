#include "HaveNextNote.h"

void HaveNextNote::setTouchId(int id)
{
	Note::setTouchId(id);
	auto&& lockNextNote = nextNote.lock();
	if (lockNextNote) lockNextNote->setTouchId(id);
}

void HaveNextNote::setJudge(const JudgeResult & judgeResult)
{
	Note::setJudge(judgeResult);
	if (judgeResult.grade != JudgeGrade::INVALID) {
		auto&& lockNextNote = nextNote.lock();
		if (lockNextNote) lockNextNote->setTouchId(judgeResult.id);
	}
}

const std::vector<PointWithSlope>& HaveNextNote::getDrawLine(int div)
{
	connectLine.clear();
	auto&& lockNextNote = nextNote.lock();
	//表示される前か,次がないなら空
	if (nowTime < getJudgeTime() - playSettings.getViewNoteTime()
		|| !lockNextNote) {
		return connectLine;
	}
	if (lockNextNote->getWasJudged()) return connectLine;
	connectLine.resize(div + 1);

	//移動具合のパーセンテージを取得
	float nextNoteP = lockNextNote->getViewPercentage();
	if (nextNoteP < 0) nextNoteP = 0;
	float targetP = getViewPercentage();
	float dp = targetP - nextNoteP;
	float divP = dp / div;
	float nowP = nextNoteP;

	float initNextNoteX = lockNextNote->getX(nextNoteP);
	float x1 = initNextNoteX;
	float x3 = getX();
	float x2 = (x1 + x3) / 2;
	if (dp > 0.2) {
		float tx = judgeLine.getCenterPosition(lockNextNote->getTarget());
		float dp2 = (dp - 0.2f) * 1.2f;
		x2 += (tx - x2) * dp2;
	}

	//各点の座標,幅,傾きをとる
	Point lastPoint, nowPoint;
	nowPoint = std::make_pair(initNextNoteX, lockNextNote->getY(nowP));
	for (int i = 0; i <= div+1; i++, nowP += divP) {
		lastPoint = nowPoint;
		double t = static_cast<double>(i) / div;
		nowPoint.first = static_cast<float>(1 - t)*(1 - t)*x1 + 2*t*(1 - t)*x2 + t * t*x3;
		//nowPoint.first = initNextNoteX + (getX() - initNextNoteX) * i / (div);
		nowPoint.second = getY(nowP);
		if (!i) continue;
		float a = M_PI_2;
		//傾き 千年女王SHDみたいなのだと重いかも
		if (std::abs(nowPoint.first - lastPoint.first) > 0.0001) {
			a = std::atan2((nowPoint.second - lastPoint.second), (nowPoint.first - lastPoint.first));
		}
		//if (a < 0) a += M_PI;
		
		//保存
		connectLine[i-1].pos = lastPoint;
		connectLine[i-1].slope = a;
		connectLine[i-1].scale = nowP - divP;
	}

	return connectLine;
}