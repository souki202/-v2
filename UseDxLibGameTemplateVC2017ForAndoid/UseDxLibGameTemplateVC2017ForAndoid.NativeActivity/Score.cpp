#include "Score.h"

Score::Score(int level, int totalNotes)
{
	initScore(level, totalNotes);
}

void Score::initScore(int level, int totalNotes)
{
	level = std::max(level, 1);
	int maxScore = level * 50000;
	maxExScore = totalNotes * 2;

	//スコアに対する実質コンボ数を計算
	float substanceTotalNotes = 0;
	int num = 0;
	while (++num <= totalNotes) {
		substanceTotalNotes += 1 + std::min(num, 100) / 100.f;
	}
	//各ノートのスコア計算
	eachNoteScore = static_cast<int>(std::ceil(maxScore / substanceTotalNotes));

	gauge.setMaxExScore(maxExScore);
}

void Score::draw()
{
	gauge.draw();
	number.draw();
}

void Score::update()
{
	//スコアの数字
	number.update();
	//ゲージ
	gauge.update();
}

void Score::addScore(const JudgeGrade & grade, int combo)
{
	int addScore = eachNoteScore * (combo >= 100 ? 200 : 100 + combo) / 100;
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
