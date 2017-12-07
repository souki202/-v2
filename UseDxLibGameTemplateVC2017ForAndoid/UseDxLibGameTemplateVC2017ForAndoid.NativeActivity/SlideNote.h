#pragma once
#include "HaveNextNote.h"

class SlideNote : public HaveNextNote {
public:
	SlideNote();
	~SlideNote() {};

	virtual void setNextNote(const std::shared_ptr<Note>& next);
	void setIsFirstNote(bool b = false);
private:
	bool isFirstNote = true;

};