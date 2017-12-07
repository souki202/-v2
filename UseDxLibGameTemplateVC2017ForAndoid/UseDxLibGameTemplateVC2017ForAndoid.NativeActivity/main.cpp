#include <stdio.h>
#include "Form.h"

using namespace CommonSettings;

// プログラムは android_main から始まります
int android_main(void)
{
	SetUseDXArchiveFlag(FALSE);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);//ウィンドウサイズ
	if (DxLib_Init() == -1) {
		return -1;
	}

	Form Fmain;

	// 描画先を裏画面に変更
	SetDrawScreen(DX_SCREEN_BACK);
	while (1) {
		if (ProcessMessage() != 0 || keyInput.getPressFrame(KEY_INPUT_ESCAPE)) {
			break;//ウィンドウの×ボタンまたはEscキー押されたらループを抜ける
		}
		ClearDrawScreen();

		//キーボード, マウスの状態を更新
		keyInput.update();
		mouseInput.update();
		touchInput.update();

		if (!Fmain.update()) {
			break;
		}
		ScreenFlip();//裏画面を反映
	}

	DxLib_End();
	return 0;
}