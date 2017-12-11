#pragma once
#include "Image.h"

class ScoreGauge {
public:
	ScoreGauge();
	~ScoreGauge() {};

	void draw();
	void update();
	void setExScore(int exScore) { this->exScore = exScore; };
	void setMaxExScore(int exScore) { maxExScore = exScore; };
private:
	Image bg;
	int maxExScore = 1;
	int exScore = 1;
	static constexpr float BASE_X = 335.f;
	static constexpr int MAX_GAUGE_WIDTH = 721;
	int gaugeWidth = 0;
	int gaugeHeight = 36;
};