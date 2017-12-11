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
	//�\�������O��,�����Ȃ��Ȃ��
	if (nowTime < getJudgeTime() - playSettings.getViewNoteTime()
		|| !nextNote) {
		return connectLine;
	}
	if (nextNote->getWasJudged()) return connectLine;
	connectLine.resize(div + 1);

	//�ړ���̃p�[�Z���e�[�W���擾
	float nextNoteP = nextNote->getViewPercentage();
	if (nextNoteP < 0) nextNoteP = 0;
	float targetP = getViewPercentage();
	float dp = targetP - nextNoteP;
	float divP = dp / div;
	float nowP = nextNoteP;

	float initNextNoteX = nextNote->getX(nextNoteP);
	float x1 = initNextNoteX;
	float x3 = getX();
	float x2 = (x1 + x3) / 2;
	if (dp > 0.2) {
		float tx = judgeLine.getCenterPosition(nextNote->getTarget());
		float dp2 = (dp - 0.2f) * 1.2f;
		x2 += (tx - x2) * dp2;
	}

	//�e�_�̍��W,��,�X�����Ƃ�
	Point lastPoint, nowPoint;
	nowPoint = std::make_pair(initNextNoteX, nextNote->getY(nowP));
	for (int i = 0; i <= div+1; i++, nowP += divP) {
		lastPoint = nowPoint;
		double t = static_cast<double>(i) / div;
		nowPoint.first = static_cast<float>(1 - t)*(1 - t)*x1 + 2*t*(1 - t)*x2 + t * t*x3;
		//nowPoint.first = initNextNoteX + (getX() - initNextNoteX) * i / (div);
		nowPoint.second = getY(nowP);
		if (!i) continue;
		float a = M_PI_2;
		//�X�� ��N����SHD�݂����Ȃ̂��Əd������
		if (std::abs(nowPoint.first - lastPoint.first) > 0.0001) {
			a = std::atan2((nowPoint.second - lastPoint.second), (nowPoint.first - lastPoint.first));
		}
		//if (a < 0) a += M_PI;
		
		//�ۑ�
		connectLine[i-1].pos = lastPoint;
		connectLine[i-1].slope = a;
		connectLine[i-1].scale = nowP - divP;
	}

	return connectLine;
}