#include "SelectMusic.h"

void SelectMusic::update()
{
	MusicInfo musicInfo("Assets/Musics/Sample/");
	factory.setNewScene<Play>(musicInfo, 1);
}
