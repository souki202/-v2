#pragma once
#include "HaveNextNote.h"
#include "FlickDirection.h"

class FlickNote : public HaveNextNote {
public:
	FlickNote();
	~FlickNote() {};

	virtual void draw();
	virtual void setDirectionByLastNote(const std::shared_ptr<Note>& lastNote);
	virtual void setDirectionByNextNote(const std::shared_ptr<Note>& nextNote);
	void setDirection(const FlickDirection& d); //0Left 1Right

	void setType(NoteType type);
private:
	FlickDirection direction = FlickDirection::INVALID;
	static constexpr int LINE_WIDTH = 24;
};