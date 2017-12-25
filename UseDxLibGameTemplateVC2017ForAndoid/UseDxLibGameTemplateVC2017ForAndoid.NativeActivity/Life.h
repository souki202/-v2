#pragma once
#include "Image.h"
#include "Timer.h"
#include "JudgeGrade.h"
#include "PlaySettings.h"
#include "GaugeType.h"
#include "ResultRecord.h"

class Life {
public:
	Life();
	~Life() {};

	void update();
	void draw();
	void setGaugeType(const GaugeType& gaugeType);
	void setJudge(const JudgeGrade& grade);
	const float& getLife() const { return life; };
	void setRecordLifeInterval(float time) { recordLifeInterval = time; };
	void startRecord();
	const std::array<float, ResultRecord::NUM_OF_LIFE_HISTORY>& getLifeHistory() const { return lifeHistry; };
private:
	Timer recTimer;
	GaugeType gaugeType = GaugeType::NORMAL;
	Image bg;
	int color = 0xffffff;
	static constexpr float MAX_LIFE = 100.f;
	static constexpr float BASE_ADD_LIFE = 0.24f;
	static constexpr float BASE_SUB_LIFE = 8.f;
	static constexpr float GAUGE_MAX_WIDTH = 208.f;
	float addPower = 1.f, subPower = 1.f;
	float life = MAX_LIFE;
	float lifeWidth = 0;
	float recordLifeInterval = 1;
	float nextRecordLifeTime = 0;
	int recCnt = 0;
	bool hasStartedRec = false;
	std::array<float, ResultRecord::NUM_OF_LIFE_HISTORY> lifeHistry = { { 0 } };
};