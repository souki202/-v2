#pragma once
#include <memory>
#include "Image.h"
#include "NoteCommon.h"
#include "PlaySettings.h"
#include "JudgeLine.h"
#include "Debug.h"
#include "Judge.h"
#include "Bomb.h"

class Note {
public:
	Note() { nowTime = 0; };
	virtual ~Note() {};

	virtual void update();
	virtual void draw();

	virtual void setting(int target, float appear, int judgeTime, int uid, int id = 0);
	void setNowTime(int t) { nowTime = t; };
	
	const int& getJudgeTime() const { return judgeTime; };
	const int& getId() const { return id; };
	const int& getUid() const { return uid; };
	const int& getTarget() const { return target; };

	float getX() const { return pos.first; }; //画面外ならINFINITYを返す
	virtual float getX(float p); //画面外ならINFINITYを返す 進行割合を入れるver
	float getY() const { return pos.second; }; //画面外ならINFINITYを返す
	virtual float getY(float p); //画面外ならINFINITYを返す 進行割合を入れるver
	virtual float getViewPercentage();

	const NoteType& getType() const { return type; };
	virtual void setType(NoteType type);

	const JudgeTiming& getJudgeTiming() const { return judgeTiming; };

	virtual void setNextNote(const std::shared_ptr<Note>& next) {};
	virtual void setDirectionByLastNote(const std::shared_ptr<Note>& lastNote) {};
	virtual void setDirectionByNextNote(const std::shared_ptr<Note>& nextNote) {};

	virtual void setJudge(const JudgeResult& judgeResult);
	bool getWasJudged() const { return wasJudged; };
	virtual void setIsFirstNote(bool b) {};

	virtual void setTouchId(int id) { touchId = id; };
	const int& getTouchId() const { return touchId; };
protected:
	Bomb bomb;
	Image noteImg;
	NoteType type;
	int id;
	float appearPos;
	int target;
	int nowTime;
	bool wasJudged = false;
	JudgeTiming judgeTiming = JudgeTiming::TOUCH;
	int touchId = -1;

private:
	int judgeTime;
	int uid = -1;
	Point pos;
	float p;

};