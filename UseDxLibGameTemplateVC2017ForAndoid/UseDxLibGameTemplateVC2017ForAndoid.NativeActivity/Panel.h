#pragma once
#include "MouseListener.h"
#include "LayerObject.h"
#include "Image.h"

class Panel : public MouseListener, public HaveUuid {
public:
	Panel(const std::shared_ptr<LayerObject<Panel>>& p);
	virtual ~Panel() { if (panels) panels->removeObject(getUuid()); };

	virtual void update() = 0;
	virtual void draw() = 0;

	const std::shared_ptr<LayerObject<Panel>>& getPanels() const { return panels; };
	const std::pair<int, int>& getPosition() const { return pos; };
	void setPosition(const std::pair<int, int>& pos) { this->pos = pos; };
	virtual void setArea(const std::pair<int, int>& leftUp, const std::pair<int, int>& rightBottom);

	virtual void changeDrawPanel() { SetDrawScreen(screen.getHandle()); ClearDrawScreen(); };
	virtual void changeDefaultDrawScreen() { SetDrawScreen(Screen::getScreen()); screen.draw(); DrawFormatString(100, 100, 0xffffff, "faa"); };
	const std::pair<int, int>& getSize() const { return size; };

private:
	std::pair<int, int> pos = std::make_pair(0, 0);
	std::pair<int, int> size = std::make_pair(CommonSettings::WINDOW_WIDTH, CommonSettings::WINDOW_HEIGHT);
	std::shared_ptr<LayerObject<Panel>> panels;
protected:
	Image screen;
};