#include "Play.h"

Play::Play(const MusicInfo& musicInfo, int difficulty)
	: musicInfo(musicInfo), difficulty(difficulty)
{
	musicScore.loadMusicScore(musicInfo.getFilePath() + static_cast<char>('0' + difficulty) + ".tsv");
}

void Play::update()
{
	musicScore.update();
}

void Play::draw()
{
	DrawString(300, 300, "Play", 0xffffff);
	musicScore.draw();

#ifdef DEBUG
	auto& touchLines = touchInput.getTouchLine();
	for (auto& x : touchLines) {
		int c = playPositions.getCenterPosition(x.second);
		int w = playPositions.getLineWidth();
		DrawBox(c - w/2, 0, c + w/2, CommonSettings::WINDOW_HEIGHT, 0xffffff, true);
	}

	auto& touchHoldInitLines = touchInput.getHoldInitLine();
	for (auto& x : touchHoldInitLines) {
		int c = playPositions.getCenterPosition(x.second);
		int w = playPositions.getLineWidth();
		DrawBox(c - w / 2, 0, c + w / 2, CommonSettings::WINDOW_HEIGHT, 0xffff00, true);
	}

	auto& touchHoldLines = touchInput.getHoldLine();
	for (auto& x : touchHoldLines) {
		int c = playPositions.getCenterPosition(x.second);
		int w = playPositions.getLineWidth();
		DrawBox(c - w / 2, 0, c + w / 2, CommonSettings::WINDOW_HEIGHT, 0xff00ff, true);
	}

	auto& touchFlickLines = touchInput.getFlickLine();
	for (auto& x : touchFlickLines) {
		int c = playPositions.getCenterPosition(x.second.first);
		int w = playPositions.getLineWidth();
		if (x.second.second == FlickDirection::FLICK_L) {
			DrawBox(c - w / 2, 0, c + w / 2, CommonSettings::WINDOW_HEIGHT, 0x0000ff, true);
		}
		else if (x.second.second == FlickDirection::FLICK_R) {
			DrawBox(c - w / 2, 0, c + w / 2, CommonSettings::WINDOW_HEIGHT, 0xff0000, true);
		}
	}
#endif
}

void Play::loadMusic()
{
}
