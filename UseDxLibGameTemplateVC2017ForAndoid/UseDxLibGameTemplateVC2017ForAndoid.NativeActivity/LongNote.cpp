#include "LongNote.h"

LongNote::LongNote()
{
	type = NoteType::LN;
	noteImg = noteImageManager.getNoteImage(type);
}
