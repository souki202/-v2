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
	judgeLine.draw();
	musicScore.draw();

#ifdef DEBUG
#endif
}

void Play::loadMusic()
{
}
