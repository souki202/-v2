#include "LongNote.h"

LongNote::LongNote()
{
	setType(NoteType::LN);
	judgeTiming = JudgeTiming::RELEASE_INIT;
}

void LongNote::draw()
{
	//次ノートが未判定で残っているならノート描画
	auto&& lockNextNote = nextNote.lock();
	if (!wasJudged || (lockNextNote && wasJudged && !lockNextNote->getWasJudged())) {
		{
			auto& points = getDrawLine();
			float dx[2], dy[2];
			float vx[4], vy[4];
			int w = judgeLine.GET_JUDGE_SIZE() / 2;
			for (int i = 0; i < static_cast<int>(points.size()) - 1; i++) {
				dx[0] = std::abs(points[i].scale * w * std::sin(points[i].slope));
				dy[0] = -(points[i].scale * w * std::cos(points[i].slope));
				dx[1] = std::abs(points[i+1].scale * w * std::sin(points[i+1].slope));
				dy[1] = -(points[i+1].scale * w * std::cos(points[i+1].slope));
				if (!(isFirstNote || !lockNextNote)) {
					if (!i) {
						dy[0] = 0;
						dx[0] = points[i].scale * w;
					}
					else if (i == static_cast<int>(points.size()) - 2) {
						dy[1] = 0;
						dx[1] = points[i + 1].scale * w;
					}
				}

				vx[0] = points[i].pos.first - dx[0];
				vx[1] = points[i].pos.first + dx[0];
				vx[2] = points[i + 1].pos.first + dx[1];
				vx[3] = points[i + 1].pos.first - dx[1];
				vy[0] = points[i].pos.second - dy[0];
				vy[1] = points[i].pos.second + dy[0];
				vy[2] = points[i + 1].pos.second + dy[1];
				vy[3] = points[i + 1].pos.second - dy[1];
				DrawModiGraphF(vx[0], vy[0], vx[1], vy[1], vx[2], vy[2], vx[3], vy[3],
					           noteImageManager.getWhiteImage().getHandle(), true
				);
			}
		}
		if (wasJudged) noteImg.draw();
		HaveNextNote::draw();
	}
	else bomb.draw();

#ifdef DEBUG
	//if (touchId >= 0) {
	//	DrawFormatString(noteImg.getPosition().first, noteImg.getPosition().second, 0xffffff, "LN");
	//}
	//if (nextNote) {
	//	DrawFormatString(noteImg.getPosition().first + 50, noteImg.getPosition().second, 0xffffff, "nextId:%d", nextNote->getUid());
	//}
#endif
}

void LongNote::update()
{
	bomb.setParticleX(getX());
	HaveNextNote::update();
	auto&& lockNextNote = nextNote.lock();
	if (lockNextNote && lockNextNote->getWasJudged()) {
		bomb.stopParticle();
	}
}

void LongNote::setNextNote(const std::shared_ptr<Note>& next)
{
	HaveNextNote::setNextNote(next);
	if (next) judgeTiming = JudgeTiming::TOUCH;
}

float LongNote::getViewPercentage()
{
	float p = HaveNextNote::getViewPercentage();
	auto&& lockNextNote = nextNote.lock();
	if (wasJudged && lockNextNote && !lockNextNote->getWasJudged()) {
		return 1.f;
	}
	return p;
}

void LongNote::setJudge(const JudgeResult & judgeResult)
{
	HaveNextNote::setJudge(judgeResult);
	//BAD以下だしたら後続消す
	auto&& lockNextNote = nextNote.lock();
	if (judgeResult.grade >= JudgeGrade::BAD
		&& judgeResult.grade != JudgeGrade::INVALID) {
		if (lockNextNote) lockNextNote->setJudge(judgeResult);
	}
	else if (lockNextNote) {
		bomb.startParticle();
	}
}
