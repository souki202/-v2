#include "Play.h"

Play::Play(const MusicInfo& musicInfo, int difficulty)
	: musicInfo(musicInfo), difficulty(difficulty)
{
	musicScore.setMusicInfo(musicInfo);
	musicScore.loadMusicScore(difficulty);
	bga.setBga(musicInfo.getFilePath());

	// リソースロード
	bombResources; 
	judgeLine;
	noteImageManager;

	intro.setMusicInfo(musicInfo);
	startDelayTimer.reset();

	updateLoadCount();
}

void Play::update()
{
	Scene::update();
	if (loading.getHasComplete()) {
		startDelayTimer.update();
		intro.update();
	}
	if (!isInitIntroTime && intro.getIsEndIntro()) {
		startDelayTimer.reset();
		musicScore.startMoveNotes();
		isInitIntroTime = true;
		isStarted = false;
	}
	if (!isStarted && intro.getIsEndIntro() && startDelayTimer.getElapsedTime() >= playSettings.getDelayTime()) {
		bga.playBga();
		musicScore.startMusic();
		isStarted = true;
	}
	if (musicScore.getIsEndMusic()) {
		musicScore.saveRecord();
		factory.setNewScene<Result>(musicScore.getResultRecord(), musicInfo);
	}
	bga.update();
	musicScore.update();
}

void Play::draw()
{
	Scene::draw();
	if (loading.getHasComplete()) {
		bga.draw();
		judgeLine.draw();
		musicScore.draw();

		intro.draw();
	}
}
