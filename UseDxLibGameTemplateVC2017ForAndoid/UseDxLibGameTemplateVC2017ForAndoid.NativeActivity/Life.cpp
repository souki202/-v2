#include "Life.h"

Life::Life()
{
	bg.setImage("Images/Play/lifebg.png");
	bg.setPosition(6.f, 0.f);
	setGaugeType(playSettings.getGaugeType());
}

void Life::update()
{
	lifeWidth = GAUGE_MAX_WIDTH * life / 100.f;
	if (life / 100.f <= 0.2) color = GetColor(110, 0, 0);
	else color = GetColor(110, 207, 112);
}

void Life::draw()
{
	DrawBox(bg.getPosition().first + 42, bg.getPosition().second + 12,
		    bg.getPosition().first + 42 + lifeWidth, bg.getPosition().second + 12 + 36,
		    color, true);
	bg.draw();
}

void Life::setGaugeType(const GaugeType & gaugeType)
{
	this->gaugeType = gaugeType;
	switch (gaugeType)
	{
	case GaugeType::HARD:
		addPower = 0.5f; subPower = 1.2f;
		break;
	case GaugeType::NORMAL:
		addPower = 1.f; subPower = 1.f;
		break;
	case GaugeType::EASY: case GaugeType::PRACTICE:
		addPower = 2.f; subPower = 0.75f;
		break;
	default:
		break;
	}
}

void Life::setJudge(const JudgeGrade & grade)
{
	float d = 0;
	switch (grade)
	{
	case JudgeGrade::PERFECT: d = BASE_ADD_LIFE * addPower; break;
	case JudgeGrade::GREAT: d = BASE_ADD_LIFE * addPower / 1.3f; break;
	case JudgeGrade::GOOD: d = BASE_ADD_LIFE * addPower / 2.f; break;
	case JudgeGrade::BAD: d = -BASE_SUB_LIFE * subPower / 1.75f; break;
	case JudgeGrade::POOR: d = -BASE_SUB_LIFE * subPower; break;
	default: break;
	}
	if (life > 0) life += d;
	life = std::max(life, 0.f);
}
