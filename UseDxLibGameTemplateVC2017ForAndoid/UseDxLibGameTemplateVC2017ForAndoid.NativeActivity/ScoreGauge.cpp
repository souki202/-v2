#include "ScoreGauge.h"

ScoreGauge::ScoreGauge()
{
	bg.setImage("Images/Play/scorebg.png");
	bg.setPosition(BASE_X, 0.f);
	rankSImg = LoadGraph("Images/Play/srank.png");
}

void ScoreGauge::draw()
{
	int gaugeDeltaX = 6 + 14;
	int gaugeDeltaY = 6 + 6;
	int color = 0xffffff;
	switch (rank.getRank(exScore, maxExScore))
	{
	case Rank::F: case Rank::E: case Rank::D: 
		color = GetColor(99, 172, 255);
		break;
	case Rank::C: color = GetColor(99, 255, 128); break;
	case Rank::B: color = GetColor(255, 183, 99); break;
	case Rank::A: color = GetColor(255, 99, 99); break;
	case Rank::S:
		DrawRectGraph(BASE_X + gaugeDeltaX, gaugeDeltaY, rankSGaugeX, 0, gaugeWidth, gaugeHeight, rankSImg, true, false);
		break;
	default: break;
	}
	if (color != 0xffffff) {
		DrawBox(BASE_X + gaugeDeltaX, gaugeDeltaY, BASE_X + gaugeDeltaX + gaugeWidth, gaugeDeltaY + gaugeHeight, color, true);
	}
	bg.draw();
}

void ScoreGauge::update()
{
	timer.update();
	//ゲージ設定
	gaugeWidth = static_cast<int>(MAX_GAUGE_WIDTH * static_cast<double>(exScore) / maxExScore);
	rankSGaugeX -= timer.getDeltaTime() / 4;
	if (rankSGaugeX < 0) rankSGaugeX += MAX_GAUGE_WIDTH;
}
