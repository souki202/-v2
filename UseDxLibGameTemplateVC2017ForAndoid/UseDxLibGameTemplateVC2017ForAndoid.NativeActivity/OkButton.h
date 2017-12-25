#pragma once
#include "Button.h"

class OkButton : public Button {
public:
	OkButton();
	OkButton(const Panel* panel);
	~OkButton() { for (int i = 0; i < 2; i++) DeleteGraph(rawImgs[i]); };

private:
	int rawImgs[2] = { 0 };

};