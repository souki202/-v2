#include "NoteCommon.h"
std::array<int, static_cast<int>(NoteType::INVALID)> NoteImageManager::noteImg = std::array<int, static_cast<int>(NoteType::INVALID)>();

void NoteImageManager::loadImage()
{
	int i = 1;
	noteImg[i++] = LoadGraph("Images/Play/Notes/normal.png");
	noteImg[i++] = LoadGraph("Images/Play/Notes/ln.png");
	noteImg[i++] = LoadGraph("Images/Play/Notes/relay.png");
	noteImg[i++] = LoadGraph("Images/Play/Notes/relay2.png");
	noteImg[i++] = LoadGraph("Images/Play/Notes/flickl.png");
	noteImg[i++] = LoadGraph("Images/Play/Notes/flickr.png");
}
