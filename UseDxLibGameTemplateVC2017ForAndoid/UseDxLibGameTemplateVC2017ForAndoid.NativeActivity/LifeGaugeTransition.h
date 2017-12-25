#pragma once
#include "Image.h"
#include "ResultRecord.h"
#include "Timer.h"

class LifeGaugeTransition {
public:
	LifeGaugeTransition();
	~LifeGaugeTransition() {};

	void draw();
	void update();
	void setGauge(const lifeHistoryType& result) { hist = result; };
	void startDrawGauge() { timer.reset(); nextDrawTime = 0; nowDrawIndex = 0; };
private:
	Timer timer;
	Image gaugeScreen;
	lifeHistoryType hist;
	int drawLineInterval = 4;
	int nextDrawTime = 0;
	int nowDrawIndex = 0;
	static constexpr int MAX_GAUGE_HEIGHT = 200;

	Image gradImg;
};