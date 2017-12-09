#pragma once
#include "Note.h"

struct PointWithSlope {
	Point pos;
	float slope;
	float scale;
};

class HaveNextNote : public Note {
public:
	HaveNextNote() {};
	virtual ~HaveNextNote() {};

	virtual void draw() { Note::draw(); /*if(nextNote)DrawFormatString(300, 16*getUid(), 0xffffff, "next:%d", nextNote->getUid()); */};
	virtual void setNextNote(const std::shared_ptr<Note>& next) { nextNote = next; };
	const std::shared_ptr<Note>& getNextNote() const { return nextNote; };
	virtual void setTouchId(int id) { Note::setTouchId(id); if (nextNote) nextNote->setTouchId(id); };

	virtual void setJudge(const JudgeResult& judgeResult);

	virtual const std::vector<PointWithSlope>& getDrawLine(int div = 24); //2‚Â‚Ìƒm[ƒgŠÔ‚ğ‚Â‚È‚®ü‚Ìæ“¾
protected:
	std::shared_ptr<Note> nextNote;

private:
	std::vector<PointWithSlope> connectLine;
};