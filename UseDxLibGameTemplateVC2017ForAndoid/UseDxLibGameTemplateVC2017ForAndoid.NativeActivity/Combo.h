#pragma once
#include <memory>
#include "CommonSettings.h"
#include "MyFuncs.h"
#include "Image.h"

class Combo {
public:
	Combo();
	~Combo();

	void draw();
	void update() {};
	int addCombo(); //return 現在のコンボ数
	void resetCombo() { nowCombo = 0; imgs.clear(); };
	int getCombo() const { return nowCombo; };
	int getMaxCombo() const { return maxCombo; };
private:
	int nowCombo = 0, maxCombo = 0;
	int* rawImage = nullptr;
	Image comboTextImg;
	std::vector<std::unique_ptr<Image>> imgs;
	static constexpr int NUMBER_WIDTH = 48;
	static constexpr float BASE_X = CommonSettings::WINDOW_WIDTH - 216;
	static constexpr float BASE_Y = 178;
};