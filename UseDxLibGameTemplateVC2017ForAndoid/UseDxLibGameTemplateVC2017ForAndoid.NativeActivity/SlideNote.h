#pragma once

#include "LongNote.h"

class SlideNote : public LongNote {
public:
	SlideNote();
	~SlideNote() {};

	virtual float getX(float p);

	virtual void setJudge(const JudgeResult& judgeResult);
	virtual void setNextNote(const std::shared_ptr<Note>& next);
	virtual void setIsFirstNote(bool b) { isFirstNote = b; updateNoteType(); };
	void updateNoteType();
private:

};