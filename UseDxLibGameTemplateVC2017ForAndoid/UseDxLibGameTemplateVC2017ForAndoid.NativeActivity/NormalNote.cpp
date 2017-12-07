#include "NormalNote.h"

NormalNote::NormalNote()
{
	type = NoteType::NORMAL;
	noteImg = noteImageManager.getNoteImage(type);
}
