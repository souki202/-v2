#include "SelectMusic.h"

void SelectMusic::update()
{
	MusicInfo musicInfo("Assets/Musics/started/");
	factory.setNewScene<Play>(musicInfo, 1);
}
