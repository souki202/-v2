#include "ScoreNumber.h"

ScoreNumber::ScoreNumber()
{
	//画像読み込み
	LoadDivGraph("Images/Play/scorenumber.png", 10, 10, 1, 24, 30, numberImg);

	for (int i = 0; i < static_cast<int>(scoreImg.size()); i++) {
		scoreImg[i].setAlpha(128);
		scoreImg[i].setImage(numberImg[0]);
		scoreImg[i].setPosition(BASE_X + 140 + i * 24.f, 54.f);
		scoreImg[i].setAlign(Align::Horizontal::CENTER, Align::Vertical::MIDDLE);
	}
	scoreImg.back().setAlpha(255);
}

void ScoreNumber::draw()
{
	for (auto& x : scoreImg) x.draw();
#ifdef DEBUG
	DrawFormatString(100, 100, 0xffffff, "score:%d", nowScore);
#endif
}

void ScoreNumber::update()
{
	timer.update();
	int t = std::min(timer.getElapsedTime(), 500);
	drawScore = MyEase::easeOut(t, 500, lastScore, nowScore);
	drawScore = std::min(drawScore, static_cast<int>(std::pow(10, MAX_DIGITS) - 1));

	//スコア表示用の設定
	std::string scoreStr = MyFuncs::to_string(drawScore);
	std::reverse(scoreStr.begin(), scoreStr.end());
	if (scoreStr.size() > MAX_DIGITS) {
		return;
	}
	//上の桁から
	for (int i = 0; i < static_cast<int>(scoreStr.size()); i++) {
		int index = scoreStr[i] - '0';
		if (index < 0 || 9 < index) {
			break;
		}
		scoreImg[MAX_DIGITS - i - 1].setAlpha(255);
		scoreImg[MAX_DIGITS - i - 1].setImage(numberImg[scoreStr[i] - '0']);
	}
}
