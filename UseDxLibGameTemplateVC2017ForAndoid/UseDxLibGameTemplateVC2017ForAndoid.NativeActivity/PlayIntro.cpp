#include "PlayIntro.h"

PlayIntro::PlayIntro()
{
	bg.setIsPremulti(true);
	bg.setImage("Images/Play/intro.png");
	//font
	largeFont = LoadFontDataToHandle("Font/36px.dft");
	normalFont = LoadFontDataToHandle("Font/30px.dft");
	titleStr.setIsPremulti(true);
	titleStr.setFont(largeFont);
	titleStr.setPosition(CommonSettings::WINDOW_WIDTHF / 2.f, 462.f);
	titleStr.setAlign(Align::Horizontal::CENTER, Align::Vertical::MIDDLE);
	titleStr.setColor(0xffffff);
	artistStr.setIsPremulti(true);
	artistStr.setFont(normalFont);
	artistStr.setPosition(CommonSettings::WINDOW_WIDTHF / 2.f, 540.f);
	artistStr.setAlign(Align::Horizontal::CENTER, Align::Vertical::MIDDLE);
	artistStr.setColor(0xffffff);
}

void PlayIntro::update()
{
	timer.update();
	int t = timer.getElapsedTime() - playSettings.getPlayIntroTime() + fadeOutTime;
	screenAlpha = MyEase::easeInOut(t, fadeOutTime, 255, 0, true);
	screen.setAlpha(screenAlpha);
}

void PlayIntro::draw()
{
	if (!getHasEndedIntro()) {
		////黒背景
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 0, CommonSettings::WINDOW_WIDTH, CommonSettings::WINDOW_HEIGHT, 0, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		SetDrawScreen(screen.getHandle());
		ClearDrawScreen();

		bg.draw();
		coverImg.draw();

		titleStr.draw();
		artistStr.draw();

		SetDrawScreen(Screen::getScreen());
		screen.draw();
	}
}

void PlayIntro::setMusicInfo(const MusicInfo & musicInfo)
{
	this->musicInfo = musicInfo; timer.reset();
	coverImg = this->musicInfo.getCover();
	coverImg.setImage(this->musicInfo.getFilePath() + "title.png");
	coverImg.setPosition(CommonSettings::WINDOW_WIDTHF / 2.f, 203.f);
	coverImg.setAlign(Align::Horizontal::CENTER, Align::Vertical::MIDDLE);
	
	titleStr.setString(musicInfo.getTitle());
	artistStr.setString(musicInfo.getArtist());

	SetUseASyncLoadFlag(false);
	SetUsePremulAlphaConvertLoad(true);
	screenHandle = MakeScreen(CommonSettings::WINDOW_WIDTH, CommonSettings::WINDOW_HEIGHT, true);
	screen.setIsPremulti(true);
	screen.setImage(screenHandle);
	SetUsePremulAlphaConvertLoad(false);
	SetUseASyncLoadFlag(true);
}

void PlayIntro::startIntro()
{
	float scale = MyFuncs::calcScaleInWindow(
		coverImg.getImageSize().first, coverImg.getImageSize().second,
		346.f, 346.f);
	coverImg.setScale(scale, scale);
	timer.reset();
}
