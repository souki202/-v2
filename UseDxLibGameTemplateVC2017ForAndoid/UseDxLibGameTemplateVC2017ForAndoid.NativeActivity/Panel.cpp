#include "Panel.h"

Panel::Panel(const std::shared_ptr<LayerObject<Panel>>& p)
	: MouseListener(), HaveUuid()
{
	panels = p;
}

void Panel::setArea(const std::pair<int, int>& leftUp, const std::pair<int, int>& rightBottom)
{
	MouseListener::setArea(leftUp, rightBottom);
	pos = leftUp;
	size = std::make_pair(rightBottom.first - leftUp.first, rightBottom.second - leftUp.second);
	screen.setImage(MakeScreen(size.first, size.second, true));
	screen.setPosition(pos);
}
