#pragma once
#include "DxLib.h"
#include "CommonSettings.h"
#include "Image.h"
#include "MusicInfo.h"
#include "Timer.h"
#include "PlaySettings.h"
#include "Easing.h"
#include "ViewString.h"
#include "MyFuncs.h"

class PlayIntro {
public:
	PlayIntro();
	PlayIntro(const MusicInfo& musicInfo) : musicInfo(musicInfo) {};
	~PlayIntro() { DeleteFontToHandle(largeFont); DeleteFontToHandle(normalFont); DeleteGraph(screenHandle); };

	void update();
	void draw();
	void setMusicInfo(const MusicInfo& musicInfo);
	bool getHasEndedIntro() const { return timer.getElapsedTime() >= playSettings.getPlayIntroTime(); };
	void startIntro();
private:
	Timer timer;
	MusicInfo musicInfo;
	Image bg;
	Image coverImg;
	Image screen;
	int screenHandle = 0;
	int screenAlpha = 255;
	int fadeOutTime = 500;
	int largeFont = 0, normalFont = 0;
	ViewString titleStr, artistStr;
};