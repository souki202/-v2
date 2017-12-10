#include "HaveNextNote.h"

void HaveNextNote::setJudge(const JudgeResult & judgeResult)
{
	Note::setJudge(judgeResult);
	if (judgeResult.grade != JudgeGrade::INVALID) {
		if (nextNote) nextNote->setTouchId(judgeResult.id);
	}
}

const std::vector<PointWithSlope>& HaveNextNote::getDrawLine(int div)
{
	connectLine.clear();
	//表示される前か,次がないなら空
	if (nowTime < getJudgeTime() - playSettings.getViewNoteTime()
		|| !nextNote) {
		return connectLine;
	}
	if (nextNote->getWasJudged()) return connectLine;
	connectLine.resize(div + 1);

	//移動具合のパーセンテージを取得
	float nextNoteP = nextNote->getViewPercentage();
	if (nextNoteP < 0) nextNoteP = 0;
	float targetP = getViewPercentage();
	float dp = targetP - nextNoteP;
	float divP = dp / div;
	float nowP = nextNoteP;

	float initNextNoteX = nextNote->getX(nextNoteP);

	Point lastPoint, nowPoint;
	nowPoint = std::make_pair(initNextNoteX, nextNote->getY(nowP));
	for (int i = 0; i <= div+1; i++, nowP += divP) {
		lastPoint = nowPoint;
		nowPoint.first = initNextNoteX + (getX() - initNextNoteX) * i / (div);
		nowPoint.second = getY(nowP);
		if (!i) continue;
		float a = M_PI_2;
		//傾き atan2なので千年女王SHDみたいなのだと重いかも
		if (std::abs(nowPoint.first - lastPoint.first) > 0.01) {
			a = std::atan((nowPoint.second - lastPoint.second) / (nowPoint.first - lastPoint.first));
		}
		
		//保存
		connectLine[i-1].pos = lastPoint;
		connectLine[i-1].slope = a;
		connectLine[i-1].scale = nowP - divP;
	}

	return connectLine;
}