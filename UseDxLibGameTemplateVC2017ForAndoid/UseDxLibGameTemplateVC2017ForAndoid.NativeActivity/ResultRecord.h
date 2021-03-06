#pragma once
#include <array>
#include "JudgeGrade.h"


struct ResultRecord {
	static constexpr int NUM_OF_LIFE_HISTORY = 488;
	int totalNotes = 1;
	int score = 0;
	int exScore = 0;
	float life = 0;
	int difficulty = 1;
	int combo = 0;

	std::array<float, ResultRecord::NUM_OF_LIFE_HISTORY> lifeHistry = { {0} };
	std::array<int, static_cast<int>(JudgeGrade::INVALID)> judgeCnt = { {0} };
};

using lifeHistoryType = std::array<float, ResultRecord::NUM_OF_LIFE_HISTORY>;
using judgeCountType = std::array<int, static_cast<int>(JudgeGrade::INVALID)>;