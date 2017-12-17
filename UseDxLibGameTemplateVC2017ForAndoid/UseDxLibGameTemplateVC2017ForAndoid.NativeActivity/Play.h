#pragma once
#include <string>
#include "Timer.h"
#include "MusicInfo.h"
#include "MusicScore.h"
#include "Scene.h"
#include "Debug.h"
#include "InputDevice.h"
#include "JudgeLine.h"
#include "BackGroundAnimation.h"
#include "PlayIntro.h"
#include "Result.h"
#include "ResultRecord.h"

class Play : public Scene {
public:
	Play(const MusicInfo& musicInfo, int difficulty);
	~Play() {};

	void update();
	void draw();
	void onLoadComplete() { startDelayTimer.reset(); intro.startIntro(); };
private:
	ResultRecord record;
	Timer startDelayTimer;
	int difficulty = 1;
	MusicInfo musicInfo;
	MusicScore musicScore;
	PlayIntro intro;
	BackGroundAnimation bga;
	bool isInitIntroTime = false;
	bool isStarted = false;
};