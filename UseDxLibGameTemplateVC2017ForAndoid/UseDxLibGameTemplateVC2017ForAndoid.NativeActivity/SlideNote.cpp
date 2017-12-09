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

	if (isFirstNote && next) judgeTiming = JudgeTiming::THROUGH;
	else if (isFirstNote) judgeTiming = JudgeTiming::TOUCH;
	else if (!isFirstNote && !next) judgeTiming = JudgeTiming::RELEASE;
}

void SlideNote::setIsFirstNote(bool b)
{
	isFirstNote = b;
	setNextNote(getNextNote());

	if (!isFirstNote && getNextNote()) judgeTiming = JudgeTiming::THROUGH;
	else if (isFirstNote) judgeTiming = JudgeTiming::TOUCH;
	else if (!isFirstNote && !getNextNote()) judgeTiming = JudgeTiming::RELEASE;
}
