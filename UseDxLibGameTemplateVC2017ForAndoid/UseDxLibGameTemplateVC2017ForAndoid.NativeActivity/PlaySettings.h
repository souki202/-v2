#pragma once
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include "GetFilePath.h"
#include "JudgeLine.h"
#include "GaugeType.h"
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
	bool getIsAuto() const { return isAuto; };
	const GaugeType& getGaugeType() const { return gaugeType; };

	int getDelayTime() const { return startDelayTime; };
	int getPlayIntroTime() const { return playIntroTime; };
	int getPlayEndWaitTime() const { return playEndWaitTime; };
private:
	static constexpr int BASE_VIEW_NOTE_TIME = 5000;
	float hiSpeed = 7.5;

	bool isAuto = true;
	GaugeType gaugeType = GaugeType::NORMAL;
	int startDelayTime = 1000;
	int playIntroTime = 5000;
	int playEndWaitTime = 1500;
};