#include "ResultBackGroundAnimation.h"

ResultBackGroundAnimation::ResultBackGroundAnimation()
{
	circleRawImgs[0] = LoadGraph("Images/Result/circle_in.png");
	circleRawImgs[1] = LoadGraph("Images/Result/circle_out.png");
	circleRawImgs[2] = LoadGraph("Images/Result/circle_mono_in.png");
	circleRawImgs[3] = LoadGraph("Images/Result/circle_mono_out.png");

	using namespace CommonSettings;
	animCircleImgs[0].setImage(circleRawImgs[0]);
	animCircleImgs[0].setPosition(100.f, 100.f);
	animCircleImgs[1].setImage(circleRawImgs[1]);
	animCircleImgs[1].setPosition(100.f, 100.f);
	animCircleImgs[2].setImage(circleRawImgs[0]);
	animCircleImgs[2].setPosition(400.f, WINDOW_HEIGHTF);
	animCircleImgs[3].setImage(circleRawImgs[1]);
	animCircleImgs[3].setPosition(400.f, WINDOW_HEIGHTF);
	animCircleImgs[4].setImage(circleRawImgs[0]);
	animCircleImgs[4].setPosition(WINDOW_WIDTHF - 100.f, WINDOW_HEIGHTF - 50.f);
	animCircleImgs[5].setImage(circleRawImgs[1]);
	animCircleImgs[5].setPosition(WINDOW_WIDTHF - 100.f, WINDOW_HEIGHTF - 50.f);
	animCircleImgs[6].setImage(circleRawImgs[2]);
	animCircleImgs[6].setPosition(WINDOW_WIDTHF - 100.f, WINDOW_HEIGHTF - 50.f);
	animCircleImgs[7].setImage(circleRawImgs[3]);
	animCircleImgs[7].setPosition(WINDOW_WIDTHF - 100.f, WINDOW_HEIGHTF - 50.f);
	for (auto& x : animCircleImgs) {
		x.setAlign(Align::Horizontal::CENTER, Align::Vertical::MIDDLE);
		x.setScale(0.4f, 0.4f);
	}
	animCircleImgs[6].setScale(0.6f, 0.6f);
	animCircleImgs[7].setScale(0.6f, 0.6f);
}

void ResultBackGroundAnimation::update()
{
	timer.update();
	for (int i = 0; i < static_cast<int>(animCircleImgs.size()); i++) {
		animCircleImgs[i].addAngle(timer.getDeltaTime() * speed[i] / 1440.f);
	}
}
