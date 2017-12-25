#include "Play.h"

Play::Play(const MusicInfo& musicInfo, int difficulty)
	: difficulty(difficulty), musicInfo(musicInfo)
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
	if (!isInitIntroTime && intro.getHasEndedIntro()) {
		startDelayTimer.reset();
		musicScore.startMoveNotes();
		isInitIntroTime = true;
		isStarted = false;
	}
	if (!isStarted && intro.getHasEndedIntro() && startDelayTimer.getElapsedTime() >= playSettings.getDelayTime()) {
		musicScore.startMusic();
		bga.playBga();
		isStarted = true;
	}
	if (musicScore.getIsEndMusic()) {
		if (myFactory.getHaveNextScene()) return;
		musicScore.saveRecord();
		myFactory.setNewScene<Result>(musicScore.getResultRecord(), musicInfo);
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
