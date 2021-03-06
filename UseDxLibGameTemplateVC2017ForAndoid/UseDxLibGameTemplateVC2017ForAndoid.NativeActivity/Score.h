#pragma once
#include "Timer.h"
#include "Image.h"
#include "JudgeGrade.h"
#include "Easing.h"
#include "MyFuncs.h"
#include "ScoreGauge.h"
#include "ScoreNumber.h"

class Score {
public:
	Score() {};
	Score(int level, int totalNotes);
	~Score() {};

	void initScore(int level, int totalNotes);
	void draw();
	void update();
	void addScore(const JudgeGrade& grade, int combo);
	int getScore() const { return score; };
	int getExScore() const { return exScore; };
private:
	Timer timer;
	ScoreGauge gauge;
	ScoreNumber number;
	int score = 0;
	int exScore = 0;
	int eachNoteScore = 0;
	int maxExScore = 1;
};