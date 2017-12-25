#pragma once
#include <memory>
#include "CommonSettings.h"
#include "Timer.h"
#include "Scene.h"
#include "Easing.h"
#include "Debug.h"
using namespace CommonSettings;
#define myFactory Factory::getInstance()

class Factory {
private:
	Factory() {};
	~Factory() {};

public:
	static Factory& getInstance() { static Factory f; return f; };
	void update() { timer.update(); };
	void draw() {
		float alpha = 0;
		if (isChange) { //次シーンがあればfadeout
			alpha = MyEase::easeInOut(timer.getElapsedTime(), fadeOut, 0, 255, true);
		}
		else alpha = MyEase::easeInOut(timer.getElapsedTime(), fadeIn, 255, 0, true);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, true);
#ifdef DEBUG
		DrawFormatString(200, 100, 0xffffff, "fade window alpha:%f, time:%d, isChange:%d", alpha, timer.getElapsedTime(), isChange);
#endif
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	};

	template <typename _class, typename... _Args>
	void setNewScene(_Args&&... __args);

	void changeScene() {
		//フェードアウト終わってから切り替え
		if (isChange && timer.getElapsedTime() >= fadeOut) {
			scene = std::move(nextScene);
			timer.reset();
			isChange = false;
		}
	};
	const std::unique_ptr<Scene>& getScene() { return scene; };
	bool getHaveNextScene() const { return (nextScene.operator bool()); };
private:
	Timer timer;
	int fadeIn = 500, fadeOut = 500;
	std::unique_ptr<Scene> scene;
	std::unique_ptr<Scene> nextScene;

	bool isChange = false;
};

template<typename _class, typename... _Args>
inline void Factory::setNewScene(_Args&&... __args)
{
	nextScene.reset(static_cast<Scene*>(new _class(std::forward<_Args>(__args)...)));
	isChange = true;
	if (!isChange) {
		timer.reset();
	}
}
