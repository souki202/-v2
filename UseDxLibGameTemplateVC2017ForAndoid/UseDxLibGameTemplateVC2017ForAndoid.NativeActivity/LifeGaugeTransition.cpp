#include "LifeGaugeTransition.h"

LifeGaugeTransition::LifeGaugeTransition()
{
	SetUseASyncLoadFlag(false);
	gaugeScreen.setImage(MakeScreen(493, 200, true));
	gaugeScreen.setPosition(727.f, 115.f);
	gaugeScreen.setAlpha(128);
	SetUseASyncLoadFlag(true);
	gradImg.setImage("Images/Result/gauge_grad.png");
}

void LifeGaugeTransition::draw()
{
	gaugeScreen.draw();
}

void LifeGaugeTransition::update()
{
	timer.update();
	SetDrawScreen(gaugeScreen.getHandle());
	while (timer.getElapsedTime() >= nextDrawTime) {
		if (nowDrawIndex >= 0 && nowDrawIndex < static_cast<int>(hist.size())) {
			DrawLine(nowDrawIndex, MAX_GAUGE_HEIGHT, 
				nowDrawIndex, static_cast<int>((100 - hist[nowDrawIndex]) * MAX_GAUGE_HEIGHT / 100), 0);
			++nowDrawIndex;
		}
		nextDrawTime += drawLineInterval;
	}
	SetDrawScreen(Screen::getScreen());
	GraphBlend(gaugeScreen.getHandle(), gradImg.getHandle(), 255, DX_GRAPH_BLEND_RGBA_SELECT_MIX,
		DX_RGBA_SELECT_BLEND_R, DX_RGBA_SELECT_BLEND_G, DX_RGBA_SELECT_BLEND_B, DX_RGBA_SELECT_SRC_A );
}
