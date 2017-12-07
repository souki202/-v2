#pragma once
namespace CommonSettings {
	//解像度
	constexpr int WINDOW_WIDTH = 1280;
	constexpr int WINDOW_HEIGHT = 720;

	//fps(60以上は垂直同期を切ってください。)
	constexpr int FRAME_RATE = 60;

	constexpr const char* GAME_TITLE = "Game"; //Unicode文字セット利用時はwchar_tに。
};