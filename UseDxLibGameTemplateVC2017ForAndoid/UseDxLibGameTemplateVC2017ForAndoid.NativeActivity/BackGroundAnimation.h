#pragma once
#include <string>
#include "DxLib.h"
#include "Timer.h"
#include "Image.h"
#include "MyFuncs.h"

class BackGroundAnimation {
public:
	BackGroundAnimation();
	~BackGroundAnimation() {};

	void draw() { bga.draw(); };
	void update();
	void setBga(const std::string& folderPath);
	void playBga(int delay = 0);
private:
	Timer timer;
	std::string imageExtensions[3]{ std::string("png"), std::string("jpg"), std::string("bmp") };
	Image bga;
	bool isMovie = false;
	float scale = 1.f;
	int delay = -1;
	bool isReservePlayMovie = false;
	bool isPlayed = false;
	int nextAdjastInterval = 0;
	int adjastInterval = 10000;
	bool wasSetPosition = false;
};