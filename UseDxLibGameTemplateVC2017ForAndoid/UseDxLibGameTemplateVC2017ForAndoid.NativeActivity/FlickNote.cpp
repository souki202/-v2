#include "FlickNote.h"

FlickNote::FlickNote()
{
	judgeTiming = JudgeTiming::FLICK_R;
}

void FlickNote::setDirectionByLastNote(const std::shared_ptr<Note>& lastNote)
{
	if (lastNote
		&& (lastNote->getType() == NoteType::FLICK_L
			|| lastNote->getType() == NoteType::FLICK_R)) {
		int lastNotePos = lastNote->getTarget();
		int nowNotePos = target;
		//‰E‚©‚ç¶‚È‚ç—¼•û¶Œü‚«
		if (lastNotePos > nowNotePos) setDirection(FlickDirection::FLICK_L);
		else if (lastNotePos < nowNotePos)  setDirection(FlickDirection::FLICK_R);
	}

}

void FlickNote::setDirectionByNextNote(const std::shared_ptr<Note>& nextNote)
{
	if (nextNote
		&& (nextNote->getType() == NoteType::FLICK_L
			|| nextNote->getType() == NoteType::FLICK_R)) {
		int nextNotePos = nextNote->getTarget();
		int nowNotePos = target;
		if (nextNotePos > nowNotePos) setDirection(FlickDirection::FLICK_R);
		else if (nextNotePos < nowNotePos) setDirection(FlickDirection::FLICK_L);
	}

}

void FlickNote::setDirection(const FlickDirection & d)
{
	direction = d;
	if (d == FlickDirection::FLICK_L) setType(NoteType::FLICK_L);
	if (d == FlickDirection::FLICK_R) setType(NoteType::FLICK_R);
}

void FlickNote::setType(NoteType type)
{
	HaveNextNote::setType(type);
	if (type == NoteType::FLICK_L) {
		judgeTiming = JudgeTiming::FLICK_L;
	}
	if (type == NoteType::FLICK_R) {
		judgeTiming = JudgeTiming::FLICK_R;
	}
}
