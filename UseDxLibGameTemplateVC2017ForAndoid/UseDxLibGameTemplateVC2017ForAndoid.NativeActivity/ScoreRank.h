#pragma once
#include <array>
#include "Image.h"

enum class Rank {
	S, A, B, C, D, E, F, INVALID
};

class ScoreRank {
public:
	ScoreRank();
	~ScoreRank() {};

	void draw();
	void update();
	const Rank& getRank(int exScore, int maxExScore);
	const Rank& getRank() const { return rank; };
	void setRank(int exScore, int maxExScore);
	float getPercentage() { return std::min(100.f * exScore / maxExScore, 100.f); };
private:
	std::array<Image, static_cast<int>(Rank::INVALID)> imgs;
	int exScore = 0, maxExScore = 1;
	Rank rank = Rank::INVALID;
};