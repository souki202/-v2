#include "SelectMusic.h"

SelectMusic::SelectMusic()
{
	updateLoadCount();
}

void SelectMusic::update()
{
	if (isFirstFrame) {
		MusicInfo musicInfo("Assets/Musics/Trinity Field/");
		myFactory.setNewScene<Play>(musicInfo, 1);
		isFirstFrame = false;
	}
}

void SelectMusic::draw()
{
	DrawFormatString(400, 400, 0xffffff, "select window");
}
