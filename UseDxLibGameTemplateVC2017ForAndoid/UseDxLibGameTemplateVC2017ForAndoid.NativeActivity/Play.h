#pragma once
#include <string>
#include "MusicInfo.h"
#include "MusicScore.h"
#include "Scene.h"
#include "Debug.h"
#include "InputDevice.h"

class Play : public Scene {
public:
	Play(const MusicInfo& musicInfo, int difficulty);
	~Play() {};

	void update();
	void draw();
	void loadMusic();
private:
	int difficulty;
	MusicInfo musicInfo;
	MusicScore musicScore;
};