#include "Button.h"
#include "Panel.h"

Button::Button(const Panel* panel)
	: MouseListener(), ButtonSubject(), HaveUuid()
{
	this->panel = panel;
}

bool Button::isOnMouse(int x, int y)
{
	std::pair<int, int> panelPos = std::make_pair(0, 0);
	if (panel != nullptr) {
		panelPos = panel->getPosition();
	}
	const auto& size = buttons[0].getSize();
	const auto& pos = buttons[0].getUpperLeftPosition();
	return panelPos.first + pos.first <= x && x <= panelPos.first + pos.first + size.first
		&& panelPos.second + pos.second <= y && y <= panelPos.second + pos.second + size.second;
}
