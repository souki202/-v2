#include "SlideNote.h"

SlideNote::SlideNote()
{
	updateNoteType();
	noteImg = noteImageManager.getNoteImage(type);
}

float SlideNote::getX(float p)
{
	if (!wasJudged || !nextNote) {
		return LongNote::getX(p);
	}
	else if(nextNote && wasJudged){
		//次ノートとの時間差
		int dt = nextNote->getJudgeTime() - getJudgeTime();
		//このノートからの時間経過量
		int dtThisNote = std::max(nowTime - getJudgeTime(), 0);
		//p
		float p = static_cast<float>(dtThisNote) / dt;
		int x = judgeLine.getCenterPosition(target);
		int nx = judgeLine.getCenterPosition(nextNote->getTarget());
		return x + p * (nx - x);
	}
	return LongNote::getX(p);
}

void SlideNote::setJudge(const JudgeResult & judgeResult)
{
	LongNote::setJudge(judgeResult);
	if (judgeResult.grade != JudgeGrade::INVALID) {
		setType(NoteType::SLIDE_RELAY);
	}
}

void SlideNote::setNextNote(const std::shared_ptr<Note>& next)
{
	if (next) {
		HaveNextNote::setNextNote(next);
	}
	updateNoteType();
}

void SlideNote::updateNoteType()
{
	type = NoteType::SLIDE;
	if (!isFirstNote && nextNote) type = NoteType::SLIDE_RELAY;
	setType(type);

	if (!isFirstNote && !getNextNote()) judgeTiming = JudgeTiming::RELEASE;
	else if (isFirstNote) judgeTiming = JudgeTiming::TOUCH;
	else judgeTiming = JudgeTiming::THROUGH;
}
