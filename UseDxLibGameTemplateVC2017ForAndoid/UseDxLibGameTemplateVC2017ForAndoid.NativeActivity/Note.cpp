#include "Note.h"

void Note::update()
{
	//���W�v�Z
	int viewTime = playSettings.getViewNoteTime();
	//x���W
	int appearX = playPositions.getCenterPosition(appearPos);
	int targetX = playPositions.getCenterPosition(target);
}

void Note::setting(int target, float appear, int judgeTime, int uid, int id)
{
	this->target = target;
	this->appearPos = appear;
	this->judgeTime = judgeTime;
	this->id = id;
	this->uid = uid;
}
