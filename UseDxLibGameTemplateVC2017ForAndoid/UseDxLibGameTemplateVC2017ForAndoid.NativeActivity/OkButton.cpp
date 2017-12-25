#include "OkButton.h"

OkButton::OkButton() : Button()
{
	LoadDivGraph("Images/Common/ok.png", 2, 2, 1, 120, 46, rawImgs);
	buttons[0].setImage(rawImgs[0]);
	buttons[1].setImage(rawImgs[0]);
	buttons[2].setImage(rawImgs[1]);
}

OkButton::OkButton(const Panel * panel) : Button(panel)
{
	LoadDivGraph("Images/Common/ok.png", 2, 2, 1, 120, 46, rawImgs);
	buttons[0].setImage(rawImgs[0]);
	buttons[1].setImage(rawImgs[0]);
	buttons[2].setImage(rawImgs[1]);
}
