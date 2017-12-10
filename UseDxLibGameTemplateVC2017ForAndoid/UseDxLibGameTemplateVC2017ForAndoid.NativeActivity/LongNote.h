#pragma once
#include "HaveNextNote.h"

class LongNote : public HaveNextNote {
public:
	LongNote();
	virtual ~LongNote() {};

	virtual void draw();
	virtual void update();
	virtual void setNextNote(const std::shared_ptr<Note>& next);

	virtual float getViewPercentage();

	virtual void setJudge(const JudgeResult& judgeResult);

protected:

private:


};