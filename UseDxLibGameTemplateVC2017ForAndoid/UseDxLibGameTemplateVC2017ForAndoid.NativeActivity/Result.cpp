#include "Result.h"

Result::Result(ResultRecord record, MusicInfo musicInfo)
	: record(record), musicInfo(musicInfo)
{
	ScoreRank scoreRank;
	scoreRank.setRank(record.exScore, record.totalNotes * 2);
	rank = scoreRank.getRank();
	exScorePercentage = scoreRank.getPercentage();
	judgeResult.setJudgeCount(record.judgeCnt, record.judgeCnt);
	judgeResult.setScore(record.score, record.score, record.exScore, record.exScore);
	judgeResult.setCombo(record.combo, record.combo);

	//font
	smallFont = LoadFontDataToHandle("Font/24px.dft");
	normalFont = LoadFontDataToHandle("Font/30px.dft");
	judgeResult.setFont(normalFont, smallFont);

	//クリア状態
	isClear = record.life > 0 || playSettings.getGaugeType() == GaugeType::PRACTICE;
	isClear = true;
	if (isClear) bg.setImage("Images/Result/clear_bg.png");
	else bg.setImage("Images/Result/failed_bg.png");

	//タイトル等
	title.setString(musicInfo.getTitle());
	title.setPosition(CommonSettings::WINDOW_WIDTHF / 4.f, 165.f);
	title.setAlign(Align::Horizontal::CENTER);
	title.setColor(0x414141);
	title.setFont(normalFont);
	artist.setString(musicInfo.getArtist());
	artist.setPosition(540.f, 200.f);
	artist.setAlign(Align::Horizontal::RIGHT);
	artist.setColor(0x414141);
	artist.setFont(smallFont);
	difficulty.setString(MyFuncs::to_string(musicInfo.getLevel(record.difficulty)));
	difficulty.setPosition(515.f, 120.f);
	difficulty.setAlign(Align::Horizontal::CENTER);
	difficulty.setColor(0x414141);
	difficulty.setFont(smallFont);
}

Result::~Result()
{
	DeleteFontToHandle(normalFont);
	DeleteFontToHandle(smallFont);
}

void Result::update()
{
	judgeResult.update();
	bga.update();
}

void Result::draw()
{
	if (loading.getHasComplete()) {
		if (isClear) {
			DrawBox(0, 0, CommonSettings::WINDOW_WIDTH, CommonSettings::WINDOW_HEIGHT, 0xffffff, true);
			bga.draw();
		}
		bg.draw();
		judgeResult.draw();
		title.draw();
		artist.draw();
		difficulty.draw();
	}
}
