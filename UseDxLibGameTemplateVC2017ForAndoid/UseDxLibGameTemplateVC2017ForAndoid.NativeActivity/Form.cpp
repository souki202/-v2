#include "Form.h"
Form::Form()
{
	noteImageManager.loadImage();
	factory.setNewScene<SelectMusic>();
}

Form::~Form()
{
}

bool Form::update()
{
	DrawFormatString(100, 100, 0xffffff, "ゲーム画面です。");
	/*
	タッチサンプル
	*/
	//全てのタッチの情報を取得
	decltype(auto) touches = touchInput.getAllTouchInfo();

	//for文の変化形。
	//touchesのすべての要素を、1つ1つtouchに入れていく。
	//touches[i]が、touchで使えるようになった感じ
	for (auto& touch : touches) {
		DrawFormatString(
			touch.second.nowPos.first, touch.second.nowPos.second - 20,
			0xffffff, "タッチ!! time:%d, frame:%d, ID:%d",
			touch.second.time, touch.second.frame, touch.first);
	}

	factory.changeScene();

	factory.getScene()->update();
	factory.getScene()->draw();

	return true;
}