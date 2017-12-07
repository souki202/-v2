#pragma once
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include "GetFilePath.h"
#undef max
#undef min

#define playSettings PlaySettings::getInstance()

class PlaySettings {
private:
	PlaySettings() { loadConfig(); };
	~PlaySettings() {};

public:

	static PlaySettings& getInstance() { static PlaySettings p; return p; };
	void loadConfig();

	void changeHiSpeed(float d) { hiSpeed = std::max(std::min(hiSpeed + d, 10.f), 0.f); };
	const float& getHiSpeed() const { return hiSpeed; };
	int getViewNoteTime() { return static_cast<int>(BASE_VIEW_NOTE_TIME / hiSpeed); };
private:
	static constexpr int BASE_VIEW_NOTE_TIME = 1000;
	float hiSpeed = 0.5;
};