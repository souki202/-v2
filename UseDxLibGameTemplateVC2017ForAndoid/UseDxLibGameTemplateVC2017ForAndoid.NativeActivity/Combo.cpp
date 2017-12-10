#include "Combo.h"

Combo::Combo()
{
	rawImage = new int[10];
	LoadDivGraph("Images/Play/comboNumber.png", 10, 10, 1, NUMBER_WIDTH, 59, rawImage);
	comboTextImg.setImage("Images/Play/comboText.png");
	comboTextImg.setAlign(Align::Horizontal::CENTER, Align::Vertical::MIDDLE);
	comboTextImg.setPosition(BASE_X, BASE_Y + 56);
}

Combo::~Combo()
{
	for (int i = 0; i < 10; i++) {
		DeleteGraph(i);
	}
	if (rawImage != nullptr) {
		delete[] rawImage;
		rawImage = nullptr;
	}
}

void Combo::draw()
{
	if (nowCombo) {
		for (auto& x : imgs) x->draw();
		comboTextImg.draw();
	}
}

int Combo::addCombo()
{
	nowCombo++;
	imgs.clear();
	std::string comboStr = MyFuncs::to_string(nowCombo);

	//è„Ç©ÇÁåÖñàÇ…å©ÇƒÇ¢Ç≠
	for (auto& x : comboStr) {
		if (x - '0' < 0 || x - '0' > 9) continue;
		imgs.push_back(std::make_unique<Image>(rawImage[x - '0']));
		imgs.back()->setAlign(Align::Horizontal::CENTER, Align::Vertical::MIDDLE);
	}
	if (imgs.empty()) return 0; //Ç†ÇËÇ¶Ç»Ç¢ÇØÇ«0ÉRÉìÉ{

	//à íuÇ∏ÇÁÇµ
	float x = -(imgs.size() - 1.f) / 2.f * NUMBER_WIDTH;
	for (int i = 0; i < imgs.size(); i++, x += NUMBER_WIDTH) {
		imgs[i]->setPosition(BASE_X + x, BASE_Y);
	}
	return nowCombo;
}
