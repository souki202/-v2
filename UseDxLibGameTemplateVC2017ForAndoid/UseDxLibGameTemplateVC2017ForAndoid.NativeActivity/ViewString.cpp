#include "ViewString.h"
int ViewString::defaultFont = 0;

void ViewString::setString(const std::string & str)
{
	this->str = str;
	DeleteGraph(img);
	img = 0;
	if (font <= 0) font = defaultFont;
	int screenWidth = GetDrawStringWidthToHandle(str.c_str(), static_cast<int>(str.size()), font);
	width = screenWidth;
	int screenHeight = static_cast<int>(1.1423f * height + 0.7827f);
	if (!height) {
		int size;
		GetFontStateToHandle(nullptr, &size, nullptr, font);
		screenHeight = static_cast<int>(1.1423f * size + 0.7827f);
	}
	//文字有り
	if (screenWidth > 0) {
		SetUseASyncLoadFlag(false);
		img = MakeScreen(screenWidth, screenHeight, true);
		SetUseASyncLoadFlag(true);
		//描画
		SetDrawScreen(img);
		ClearDrawScreen();
		DrawFormatStringToHandle(0, 0, color, font, str.c_str());
		SetDrawScreen(DX_SCREEN_BACK);

		strImg.setImage(img);
	}
}

void ViewString::draw()
{
	if (width <= 0 && str.size() > 0) {
		setString(str);
	}
	strImg.draw();
}
