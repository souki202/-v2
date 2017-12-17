#pragma once
#include "Timer.h"
#include "Image.h"

class ResultBackGroundAnimation {
public:
	ResultBackGroundAnimation();
	~ResultBackGroundAnimation() { for (auto& img : circleRawImgs) DeleteGraph(img); };

	void update();
	void draw() { for (auto& x : animCircleImgs) x.draw(); };
private:
	Timer timer;
	std::array<int, 4> circleRawImgs;
	std::array<Image, 8> animCircleImgs;
	std::array<int, 8> speed = {1, -1, 1, -1, -1, 1, 1, -1};
};