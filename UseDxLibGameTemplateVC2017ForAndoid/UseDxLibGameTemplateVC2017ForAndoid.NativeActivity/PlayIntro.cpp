#include "PlayIntro.h"

void PlayIntro::update()
{
	timer.update();
}

void PlayIntro::draw()
{
	if (!getIsEndIntro()) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 0, CommonSettings::WINDOW_WIDTH, CommonSettings::WINDOW_HEIGHT, 0, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// とりあえずテスト
		DrawFormatString(300, 300, 0xffffff, musicInfo.getTitle().c_str());
	}
}
