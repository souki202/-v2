#include "SlideNote.h"

SlideNote::SlideNote()
{
	type = NoteType::SLIDE;
	noteImg = noteImageManager.getNoteImage(type);
}

void SlideNote::setNextNote(const std::shared_ptr<Note>& next)
{
	HaveNextNote::setNextNote(next);
	type = NoteType::SLIDE;
	if (isFirstNote && next) type = NoteType::SLIDE_RELAY;
	setType(type);
}

void SlideNote::setIsFirstNote(bool b)
{
	isFirstNote = b;
	setNextNote(getNextNote());
}
