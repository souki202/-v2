#include "SelectMusic.h"

void SelectMusic::update()
{
	MusicInfo musicInfo("Assets/Musics/Started/");
	factory.setNewScene<Play>(musicInfo, 1);
}
