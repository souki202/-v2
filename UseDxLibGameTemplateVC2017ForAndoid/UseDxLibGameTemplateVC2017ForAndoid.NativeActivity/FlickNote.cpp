#include "FlickNote.h"

FlickNote::FlickNote()
{
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
	if (d == FlickDirection::FLICK_L) type = NoteType::FLICK_L;
	if (d == FlickDirection::FLICK_R) type = NoteType::FLICK_R;
	noteImg = noteImageManager.getNoteImage(type);
}
