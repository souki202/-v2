#pragma once
#include "DxLib.h"
#include "CommonSettings.h"
#include "MusicInfo.h"
#include "Timer.h"
#include "PlaySettings.h"

class PlayIntro {
public:
	PlayIntro() {};
	PlayIntro(const MusicInfo& musicInfo) : musicInfo(musicInfo) {};
	~PlayIntro() {};

	void update();
	void draw();
	void setMusicInfo(const MusicInfo& musicInfo) { this->musicInfo = musicInfo; timer.reset(); };
	bool getIsEndIntro() const { return timer.getElapsedTime() >= playSettings.getPlayIntroTime(); };
	void startIntro() { timer.reset(); };
private:
	Timer timer;
	MusicInfo musicInfo;
};