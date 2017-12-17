#include "NowLoadingWindow.h"

void NowLoadingWindow::update()
{
	loadRaito = 1.f;
	nowLoadCount = GetASyncLoadNum();
	if (initLoadCount > 0) {
		loadRaito = 1.f - static_cast<float>(nowLoadCount) / initLoadCount;
	}
	if (loadRaito == 1.f) {
		initLoadCount = 0;
	}
}

void NowLoadingWindow::draw()
{
	if (loadRaito < 1) {
		DrawFormatString(900, 500, 0xffffff, "Now Loading");
	}
}
