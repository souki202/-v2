#include "ScoreGauge.h"

ScoreGauge::ScoreGauge()
{
	bg.setImage("Images/Play/scorebg.png");
	bg.setPosition(BASE_X, 0.f);
}

void ScoreGauge::draw()
{
	int gaugeDeltaX = 6 + 14;
	int gaugeDeltaY = 6 + 6;
	DrawBox(BASE_X + gaugeDeltaX, gaugeDeltaY, BASE_X + gaugeDeltaX + gaugeWidth, gaugeDeltaY + gaugeHeight, 0x33ff33, true);
	bg.draw();
}

void ScoreGauge::update()
{
	//ÉQÅ[ÉWê›íË
	gaugeWidth = static_cast<int>(MAX_GAUGE_WIDTH * static_cast<double>(exScore) / maxExScore);
}
