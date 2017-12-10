#include "NoteCommon.h"
void NoteImageManager::loadImage()
{
	int i = 1;
	noteImg[i++] = LoadGraph("Images/Play/Notes/normal.png");
	noteImg[i++] = LoadGraph("Images/Play/Notes/ln.png");
	noteImg[i++] = LoadGraph("Images/Play/Notes/relay.png");
	noteImg[i++] = LoadGraph("Images/Play/Notes/relay2.png");
	noteImg[i++] = LoadGraph("Images/Play/Notes/flickl.png");
	noteImg[i++] = LoadGraph("Images/Play/Notes/flickr.png");

	rawFamilyNoteImg = new int[static_cast<int>(NoteType::INVALID) * 4];
	LoadDivGraph("Images/Play/Notes/notes.png", 24, 4, 6, 154, 110, rawFamilyNoteImg);

	for (int i = 0; i < 4; i++) {
		familyNoteImg[i][1] = rawFamilyNoteImg[i + 4 * 0];
		familyNoteImg[i][2] = rawFamilyNoteImg[i + 4 * 1];
		familyNoteImg[i][3] = rawFamilyNoteImg[i + 4 * 4];
		familyNoteImg[i][4] = rawFamilyNoteImg[i + 4 * 5];
		familyNoteImg[i][5] = rawFamilyNoteImg[i + 4 * 2];
		familyNoteImg[i][6] = rawFamilyNoteImg[i + 4 * 3];
	}

	whiteImg.setImage("Images/white1x1.png");
}
