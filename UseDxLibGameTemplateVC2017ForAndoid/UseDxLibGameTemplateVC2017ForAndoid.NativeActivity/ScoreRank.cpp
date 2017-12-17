#include "ScoreRank.h"

ScoreRank::ScoreRank()
{
}

void ScoreRank::draw()
{
}

void ScoreRank::update()
{
}

const Rank& ScoreRank::getRank(int exScore, int maxExScore)
{
	setRank(exScore, maxExScore);
	return rank;
}

void ScoreRank::setRank(int exScore, int maxExScore)
{
	if (maxExScore <= 0) maxExScore = 1;
	this->exScore = exScore;
	this->maxExScore = maxExScore;
	float p = 100.f * exScore / maxExScore;
	rank = Rank::F;
	for (int i = 0; i < static_cast<int>(Rank::INVALID); i++) {
		if (p >= 100 - 11.1111 * (i + 1)) {
			rank = static_cast<Rank>(i);
			return;
		}
	}
	rank = Rank::F;
}
