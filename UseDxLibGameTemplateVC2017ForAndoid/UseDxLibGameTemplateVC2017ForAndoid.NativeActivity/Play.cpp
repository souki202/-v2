#include "Play.h"

Play::Play(const MusicInfo& musicInfo, int difficulty)
	: musicInfo(musicInfo), difficulty(difficulty)
{
	musicScore.setMusicInfo(musicInfo);
	musicScore.loadMusicScore(difficulty);

	musicScore.startMusic();
}

void Play::update()
{
	musicScore.update();
}

void Play::draw()
{
#ifdef DEBUG
	auto flickLine = touchInput.getFlickLeftLine();
	for (auto& x : flickLine) {
		int c = judgeLine.getCenterPosition(x.first);
		int w = judgeLine.getLineWidth();
		DrawBox(c - w/2, 0, c + w/2, CommonSettings::WINDOW_HEIGHT, 0xff0000, true);
	}
	flickLine = touchInput.getFlickRightLine();
	for (auto& x : flickLine) {
		int c = judgeLine.getCenterPosition(x.first);
		int w = judgeLine.getLineWidth();
		DrawBox(c - w / 2, 0, c + w / 2, CommonSettings::WINDOW_HEIGHT, 0x0000ff, true);
	}
#endif
	judgeLine.draw();
	musicScore.draw();

}

void Play::loadMusic()
{
}
