#pragma once
#include "DxLib.h"
#include "Image.h"

#define loading NowLoadingWindow::getInstance()

class NowLoadingWindow {
private:
	NowLoadingWindow() {};
	~NowLoadingWindow() {};

public:
	static NowLoadingWindow& getInstance() { static NowLoadingWindow s; return s; };
	void update();
	void draw();

	void updateLoadCount() { initLoadCount = GetASyncLoadNum(); };
	bool getHasComplete() { return GetASyncLoadNum() == 0 && externLoadCnt <= 0; };
	void addLoadCount() { ++externLoadCnt; };
	void subLoadCount() { --externLoadCnt; };
private:
	int initLoadCount = 0;
	int nowLoadCount = 0;
	int gaugeWidth = 1;
	float loadRaito = 1.f; //すべて終わっていれば1
	int externLoadCnt = 0;
};