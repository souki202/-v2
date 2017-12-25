#pragma once
#include "DxLib.h"
namespace CommonSettings {
	//解像度
	constexpr int WINDOW_WIDTH = 1280;
	constexpr int WINDOW_HEIGHT = 720;
	constexpr float WINDOW_WIDTHF = static_cast<float>(WINDOW_WIDTH);
	constexpr float WINDOW_HEIGHTF = static_cast<float>(WINDOW_HEIGHT);

	//fps(60以上は垂直同期を切ってください。)
	constexpr int FRAME_RATE = 60;

	constexpr const char* GAME_TITLE = "Game"; //Unicode文字セット利用時はwchar_tに。
};

class Screen {
private:
	Screen() {};
	~Screen() {};
public:
	static const int getScreen() { return screen; };
	static void setScreen(int val) { DeleteGraph(screen); screen = val; };

private:
	static int screen;
	static int width;
	static int height;
};