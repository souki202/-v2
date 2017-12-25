#pragma once
#include <boost/function.hpp>
#include "Factory.h"
#include "Scene.h"
#include "SelectMusic.h"
#include "ResultRecord.h"
#include "ScoreRank.h"
#include "MusicInfo.h"
#include "ViewString.h"
#include "ViewJudgeResultDetail.h"
#include "ResultBackGroundAnimation.h"
#include "LifeGaugeTransition.h"
#include "ResultThumb.h"
#include "MouseSubject.h"
#include "LayerObject.h"
#include "OkButton.h"


class Result : public Scene {
public:
	Result(ResultRecord record, MusicInfo musicInfo);
	~Result();

	void update();
	void draw();

	virtual void onLoadComplete() { lifeGauge.startDrawGauge(); thumb.calcScale(); };
private:
	MusicInfo musicInfo;
	ResultRecord record;
	ViewJudgeResultDetail judgeResult;
	LifeGaugeTransition lifeGauge;
	ResultBackGroundAnimation bga;
	ResultThumb thumb;
	Rank rank;
	float exScorePercentage = 0.f;
	bool isClear = false;
	int smallFont = 0;
	int normalFont = 0;

	ViewString title, artist, difficulty;

	Image bg;
	std::unique_ptr<LayerObject<Button>> mouseSubject;
	std::shared_ptr<OkButton> okButton;
};