#include "BackGroundAnimation.h"

BackGroundAnimation::BackGroundAnimation()
{
}

void BackGroundAnimation::update()
{
	timer.update();
	if (!isPlayed && isMovie && isReservePlayMovie && timer.getElapsedTime() >= delay) {
		PlayMovieToGraph(bga.getHandle());
		isPlayed = true;
		nextAdjastInterval = adjastInterval;
		timer.reset();
	}
	//性能によってはずれるので調整
	if(isMovie && isPlayed && timer.getElapsedTime() > nextAdjastInterval) {
		SeekMovieToGraph(bga.getHandle(), timer.getElapsedTime());
		PlayMovieToGraph(bga.getHandle());
		nextAdjastInterval += adjastInterval;
	}
	if (loading.getHasComplete()) {
		if (bga.getHandle() > 0 && !wasSetPosition) {
			using namespace CommonSettings;
			auto size = bga.getSize();
			if (size.first <= 0 || size.second <= 0) return;
			//拡大率の小さい方を優先
			scale = MyFuncs::calcScaleInWindow(size.first, size.second, WINDOW_WIDTHF, WINDOW_HEIGHTF);
			bga.setScale(scale, scale);
			bga.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
			bga.setAlign(Align::Horizontal::CENTER, Align::Vertical::MIDDLE);
			wasSetPosition = true;
		}
	}
}

void BackGroundAnimation::setBga(const std::string & folderPath)
{
	std::string filePath = folderPath + "bga.";
	bga.setImage(filePath + "ogv");
	std::ifstream ifs(filePath + "ogv");
	if (ifs.is_open()) {
		int a = 0;
		a = 5;
	}
	if (bga.getHandle() > 0) {
		isMovie = true;
	}
	if (!isMovie) {
		for (auto& ext : imageExtensions) {
			bga.setImage(filePath + ext);
			if (bga.getHandle() > 0) break;
		}
	}
	wasSetPosition = false;
}

void BackGroundAnimation::playBga(int delay)
{
	isPlayed = false;
	isReservePlayMovie = true;
	timer.reset();
}
