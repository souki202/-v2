#pragma once
#include "Image.h"
#include "JudgeGrade.h"
#include "PlaySettings.h"
#include "GaugeType.h"

class Life {
public:
	Life();
	~Life() {};

	void update();
	void draw();
	void setGaugeType(const GaugeType& gaugeType);
	void setJudge(const JudgeGrade& grade);
	const float& getLife() const { return life; };
private:
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
};