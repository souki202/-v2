#pragma once
#include "HaveNextNote.h"

enum class FlickDirection {
	FLICK_L, FLICK_R, INVALID
};

class FlickNote : public HaveNextNote {
public:
	FlickNote();
	~FlickNote() {};

	virtual void setDirectionByLastNote(const std::shared_ptr<Note>& lastNote);
	virtual void setDirectionByNextNote(const std::shared_ptr<Note>& nextNote);
	void setDirection(const FlickDirection& d); //0Left 1Right
private:
	FlickDirection direction = FlickDirection::INVALID;

};