#pragma once
#include <memory>
#include "Image.h"
#include "NoteCommon.h"
#include "PlaySettings.h"
#include "JudgeLine.h"
#include "Debug.h"

class Note {
public:
	Note() {};
	virtual ~Note() {};

	virtual void update();
	virtual void draw();

	virtual void setting(int target, float appear, int judgeTime, int uid, int id = 0);
	void setNowTime(int t) { nowTime = t; };
	
	const int& getJudgeTime() const { return judgeTime; };
	const int& getId() const { return id; };
	const int& getUid() const { return uid; };
	const int& getTarget() const { return target; };

	const NoteType& getType() const { return type; };
	void setType(NoteType type);

	virtual void setNextNote(const std::shared_ptr<Note>& next) {};
	virtual void setDirectionByLastNote(const std::shared_ptr<Note>& lastNote) {};
	virtual void setDirectionByNextNote(const std::shared_ptr<Note>& nextNote) {};
protected:
	Image noteImg;
	NoteType type;
	int id;
	float appearPos;
	int target;
	int nowTime;

private:
	int judgeTime;
	int uid = -1;
};