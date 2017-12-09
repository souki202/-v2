#pragma once
#include "LongNote.h"

class SlideNote : public LongNote {
public:
	SlideNote();
	~SlideNote() {};

	virtual void setNextNote(const std::shared_ptr<Note>& next);
	void setIsFirstNote(bool b = false);
private:
	bool isFirstNote = true;

};