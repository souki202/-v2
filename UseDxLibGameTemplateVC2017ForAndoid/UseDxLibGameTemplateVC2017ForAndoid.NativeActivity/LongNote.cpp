#include "LongNote.h"

LongNote::LongNote()
{
	setType(NoteType::LN);
	judgeTiming = JudgeTiming::RELEASE_INIT;
}

void LongNote::draw()
{
	auto& points = getDrawLine();
	for (int i = 0; i < points.size(); i++) {
		if (!i) continue;
		DrawCircle(points[i].pos.first, points[i].pos.second, points[i].scale * judgeLine.GET_JUDGE_SIZE() / 2, 0xffffff);
	}
	//ŽŸƒm[ƒg‚ª–¢”»’è‚ÅŽc‚Á‚Ä‚¢‚é‚È‚çƒm[ƒg•`‰æ
	if (!wasJudged || (wasJudged && nextNote && !nextNote->getWasJudged())) {
		HaveNextNote::draw();
	}

#ifdef DEBUG
	if (touchId >= 0) {
		DrawFormatString(noteImg.getPosition().first, noteImg.getPosition().second, 0xffffff, "LN");
	}
	if (nextNote) {
		DrawFormatString(noteImg.getPosition().first + 50, noteImg.getPosition().second, 0xffffff, "nextId:%d", nextNote->getUid());
	}
#endif
}

void LongNote::setNextNote(const std::shared_ptr<Note>& next)
{
	HaveNextNote::setNextNote(next);
	if (next) judgeTiming = JudgeTiming::TOUCH;
}

float LongNote::getViewPercentage()
{
	float p = HaveNextNote::getViewPercentage();
	if (wasJudged && nextNote && !nextNote->getWasJudged()) {
		return 1.f;
	}
	return p;
}

void LongNote::setJudge(const JudgeResult & judgeResult)
{
	HaveNextNote::setJudge(judgeResult);
	//BADˆÈ‰º‚¾‚µ‚½‚çŒã‘±Á‚·
	if (judgeResult.grade >= JudgeGrade::BAD
		&& judgeResult.grade != JudgeGrade::INVALID) {
		if (nextNote)nextNote->setJudge(judgeResult);
	}
}
