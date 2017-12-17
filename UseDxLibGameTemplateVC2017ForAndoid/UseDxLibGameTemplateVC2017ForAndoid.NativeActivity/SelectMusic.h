#pragma once
#include "Scene.h"
#include "Factory.h"
#include "Play.h"
#include "MusicInfo.h"

class SelectMusic : public Scene {
public:
	SelectMusic();
	~SelectMusic() {};

	void update();
	void draw();
private:
	bool isFirstFrame = true;
};