#include "LongNote.h"

LongNote::LongNote()
{
	setType(NoteType::LN);
	judgeTiming = JudgeTiming::RELEASE_INIT;
}

void LongNote::draw()
{
	//ŽŸƒm[ƒg‚ª–¢”»’è‚ÅŽc‚Á‚Ä‚¢‚é‚È‚çƒm[ƒg•`‰æ
	if (!wasJudged || (nextNote && wasJudged && !nextNote->getWasJudged())) {
		{
			auto& points = getDrawLine();
			float dx[2], dy[2];
			float vx[4], vy[4];
			int w = judgeLine.GET_JUDGE_SIZE() / 2;
			for (int i = 0; i < static_cast<int>(points.size()) - 1; i++) {
				dx[0] = std::abs(points[i].scale * w * std::sin(points[i].slope));
				dy[0] = std::abs(points[i].scale * w * std::cos(points[i].slope));
				dx[1] = std::abs(points[i+1].scale * w * std::sin(points[i+1].slope));
				dy[1] = std::abs(points[i+1].scale * w * std::cos(points[i+1].slope));
				vx[0] = points[i].pos.first - dx[0];
				vx[1] = points[i].pos.first + dx[0];
				vx[2] = points[i + 1].pos.first + dx[1];
				vx[3] = points[i + 1].pos.first - dx[1];
				vy[0] = points[i].pos.second - dy[0];
				vy[1] = points[i].pos.second + dy[0];
				vy[2] = points[i + 1].pos.second + dy[1];
				vy[3] = points[i + 1].pos.second - dy[1];
				if (points[i].slope > 0) {
					std::swap(vx[0], vx[1]);
					std::swap(vx[2], vx[3]);
				}

				DrawModiGraphF(vx[0], vy[0], vx[1], vy[1], vx[2], vy[2], vx[3], vy[3],
					           noteImageManager.getWhiteImg().getHandle(), true
				);
			}
		}
		HaveNextNote::draw();
		if (wasJudged) noteImg.draw();
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

void LongNote::update()
{
	HaveNextNote::update();
	if (nextNote && nextNote->getWasJudged()) {
		bomb.stopParticle();
	}
	bomb.setParticleX(getX());
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
		if (nextNote) nextNote->setJudge(judgeResult);
	}
	else if (nextNote) {
		bomb.startParticle();
	}
}
