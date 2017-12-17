#include "SlideNote.h"

SlideNote::SlideNote()
{
	updateNoteType();
	noteImg = noteImageManager.getNoteImage(type);
}

float SlideNote::getX(float p)
{
	auto&& lockNextNote = nextNote.lock();
	if (!wasJudged || !lockNextNote) {
		return LongNote::getX(p);
	}
	else if(lockNextNote && wasJudged){
		//次ノートとの時間差
		int dt = lockNextNote->getJudgeTime() - getJudgeTime();
		//このノートからの時間経過量
		int dtThisNote = std::max(nowTime - getJudgeTime(), 0);
		//p
		float p = static_cast<float>(dtThisNote) / dt;
		p = std::min(p, 1.f);
		int x = judgeLine.getCenterPosition(target);
		int nx = judgeLine.getCenterPosition(lockNextNote->getTarget());
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
	auto&& lockNextNote = nextNote.lock();
	if (!isFirstNote && lockNextNote) type = NoteType::SLIDE_RELAY;
	setType(type);

	if (!isFirstNote && !getNextNote()) judgeTiming = JudgeTiming::RELEASE;
	else if (isFirstNote) judgeTiming = JudgeTiming::TOUCH;
	else judgeTiming = JudgeTiming::THROUGH;
}
