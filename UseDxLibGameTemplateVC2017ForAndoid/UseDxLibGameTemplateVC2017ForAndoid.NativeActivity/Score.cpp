#include "Score.h"

Score::Score(int level, int totalNotes)
{
	initScore(level, totalNotes);
}

void Score::initScore(int level, int totalNotes)
{
	level = std::max(level, 1);
	int initTotalNotes = totalNotes;
	maxScore = level * 50000;
	maxExScore = totalNotes * 2;

	//�X�R�A�ɑ΂�������R���{�����v�Z
	//100�܂ł�100+combo%�A100�ȍ~��200%�̃X�R�A
	int under100 = totalNotes >= 100 ? 100 : totalNotes;
	if (totalNotes > 100) {
		totalNotes += totalNotes - under100;
	}
	totalNotes += under100 / 2;
	if (totalNotes < 0) totalNotes = 1;

	//�ō��X�R�A�v�Z
	eachNoteScore = static_cast<int>(std::ceil(static_cast<float>(maxScore) / totalNotes));
	int tmpCombo = 0;
	maxScore = 0;
	while (++tmpCombo <= initTotalNotes) {
		int addScore = static_cast<int>(static_cast<double>(eachNoteScore) * (tmpCombo > 100 ? 200 : 100 + tmpCombo) / 100);
		maxScore += addScore;
	}
	maxScore = std::max(maxScore, 1);

	gauge.setMaxExScore(maxExScore);
}

void Score::draw()
{
	gauge.draw();
	number.draw();
}

void Score::update()
{
	p = static_cast<float>(exScore) / maxExScore;

	//�X�R�A�̐���
	number.update();
	//�Q�[�W
	gauge.update();
}

void Score::addScore(const JudgeGrade & grade, int combo)
{
	int addScore = static_cast<int>(static_cast<float>(eachNoteScore) * (combo > 100 ? 200 : 100 + combo) / 100);
	switch (grade)
	{
	case JudgeGrade::PERFECT:
		score += addScore;
		exScore += 2;
		break;
	case JudgeGrade::GREAT:
		score += addScore / 2;
		exScore++;
		break;
	case JudgeGrade::GOOD:
		score += addScore / 4;
		break;
	default:break;
	}
	timer.reset();
	gauge.setExScore(exScore);
	number.setScore(score);
}
