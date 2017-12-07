#pragma once
#include "Note.h"

class HaveNextNote : public Note {
public:
	HaveNextNote() {};
	virtual ~HaveNextNote() {};

	virtual void draw() { Note::draw(); if(nextNote)DrawFormatString(300, 16*getUid(), 0xffffff, "next:%d", nextNote->getUid()); };
	virtual void setNextNote(const std::shared_ptr<Note>& next) { nextNote = next; };
	const std::shared_ptr<Note>& getNextNote() const { return nextNote; };
private:
	std::shared_ptr<Note> nextNote;

};