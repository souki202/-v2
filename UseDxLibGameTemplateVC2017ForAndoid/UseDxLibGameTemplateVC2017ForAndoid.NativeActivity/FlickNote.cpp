#include "FlickNote.h"

FlickNote::FlickNote()
{
	setDirection(FlickDirection::FLICK_R);
}

void FlickNote::draw()
{
	//フリック間の線を描画
	if (!wasJudged) {
		auto points = getDrawLine(1);
		if (points.size() >= 2) {
			float dx[2], dy[2];
			dx[0] = points[0].scale * LINE_WIDTH * std::sin(points[0].slope);
			dy[0] = points[0].scale * LINE_WIDTH * std::cos(points[0].slope);
			dx[1] = points[1].scale * LINE_WIDTH * std::sin(points[1].slope);
			dy[1] = points[1].scale * LINE_WIDTH * std::cos(points[1].slope);
			DrawModiGraphF(
				points[0].pos.first - dx[0],
				points[0].pos.second - dy[0],
				points[1].pos.first - dx[1],
				points[1].pos.second - dy[1],
				points[1].pos.first + dx[1],
				points[1].pos.second + dy[1],
				points[0].pos.first + dx[0],
				points[0].pos.second + dy[0],
				noteImageManager.getWhiteImg().getHandle(),
				true
			);
		}
	}

	HaveNextNote::draw();
}

void FlickNote::setDirectionByLastNote(const std::shared_ptr<Note>& lastNote)
{
	if (lastNote
		&& (lastNote->getType() == NoteType::FLICK_L
			|| lastNote->getType() == NoteType::FLICK_R)) {
		int lastNotePos = lastNote->getTarget();
		int nowNotePos = target;
		//右から左なら両方左向き
		if (lastNotePos > nowNotePos) setDirection(FlickDirection::FLICK_L);
		else if (lastNotePos < nowNotePos)  setDirection(FlickDirection::FLICK_R);
	}

}

void FlickNote::setDirectionByNextNote(const std::shared_ptr<Note>& nextNote)
{
	if (nextNote
		&& (nextNote->getType() == NoteType::FLICK_L
			|| nextNote->getType() == NoteType::FLICK_R)) {
		int nextNotePos = nextNote->getTarget();
		int nowNotePos = target;
		if (nextNotePos > nowNotePos) setDirection(FlickDirection::FLICK_R);
		else if (nextNotePos < nowNotePos) setDirection(FlickDirection::FLICK_L);
	}

}

void FlickNote::setDirection(const FlickDirection & d)
{
	direction = d;
	if (d == FlickDirection::FLICK_L) setType(NoteType::FLICK_L);
	if (d == FlickDirection::FLICK_R) setType(NoteType::FLICK_R);
}

void FlickNote::setType(NoteType type)
{
	HaveNextNote::setType(type);
	if (type == NoteType::FLICK_L) {
		judgeTiming = JudgeTiming::FLICK_L;
	}
	if (type == NoteType::FLICK_R) {
		judgeTiming = JudgeTiming::FLICK_R;
	}
}
