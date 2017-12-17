#pragma once
#include "Factory.h"
#include "Scene.h"
#include "SelectMusic.h"
#include "ResultRecord.h"
#include "ScoreRank.h"
#include "MusicInfo.h"
#include "ViewString.h"
#include "ViewJudgeResultDetail.h"
#include "ResultBackGroundAnimation.h"

class Result : public Scene {
public:
	Result(ResultRecord record, MusicInfo musicInfo);
	~Result();

	void update();
	void draw();
private:
	MusicInfo musicInfo;
	ResultRecord record;
	ViewJudgeResultDetail judgeResult;
	ResultBackGroundAnimation bga;
	Rank rank;
	float exScorePercentage = 0.f;
	bool isClear = false;
	int smallFont = 0;
	int normalFont = 0;

	ViewString title, artist, difficulty;

	Image bg;
};