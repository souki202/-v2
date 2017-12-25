#include <stdio.h>
#include "Form.h"
namespace boost {
	void throw_exception(std::exception const & e) { }
}

int Screen::screen = 0;
int Screen::width = 0;
int Screen::height = 0;

using namespace CommonSettings;
// プログラムは android_main から始まります
int android_main(void)
{
	SetUseDXArchiveFlag(FALSE);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);//ウィンドウサイズ
	if (DxLib_Init() == -1) {
		return -1;
	}
	SetUseASyncLoadFlag(true);
	//SetUsePremulAlphaConvertLoad(true);
	Form Fmain;

	Screen::setScreen(MakeScreen(static_cast<int>(WINDOW_WIDTH), static_cast<int>(WINDOW_HEIGHT), false));
	// 描画先を裏画面に変更
	SetDrawScreen(DX_SCREEN_BACK);
	while (1) {
		if (ProcessMessage() != 0 || keyInput.getPressFrame(KEY_INPUT_ESCAPE)) {
			break;//ウィンドウの×ボタンまたはEscキー押されたらループを抜ける
		}

		SetDrawScreen(Screen::getScreen());
		ClearDrawScreen();

		//キーボード, マウス, タッチの状態を更新
		keyInput.update();
		mouseInput.update();
		touchInput.update();

		if (!Fmain.update()) {
			break;
		}
		Fmain.draw();

		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawGraph(0, 0, Screen::getScreen(), false);
		ScreenFlip();//裏画面を反映
	}

	DxLib_End();
	return 0;
}