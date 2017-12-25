#pragma once
#include "ButtonSubject.h"
#include "MouseListener.h"
#include "HaveUuid.h"
#include "Image.h"

class Panel;

class Button : public MouseListener, public ButtonSubject , public HaveUuid {
public:
	enum class State {
		NORMAL, HOVER, PRESS, INVALID,
	};

	Button() : MouseListener(), ButtonSubject(), HaveUuid() {};
	Button(const Panel* panel);
	virtual ~Button() {};
	
	virtual void draw() { buttons[static_cast<int>(nowState)].draw(); };

	virtual void onMouse(const MouseEvent& e) { nowState = State::HOVER; };
	virtual void onClick(const MouseEvent& e) { nowState = State::PRESS; };
	virtual void onPress(const MouseEvent& e) { nowState = State::PRESS; };
	virtual void onDrag(const MouseEvent& e) { nowState = State::PRESS; };
	virtual void onRelease(const MouseEvent& e) { nowState = State::HOVER; call(e); };
	virtual void onLeave(const MouseEvent& e) { nowState = State::NORMAL; };

	virtual bool isOnMouse(int x, int y);
	virtual bool isOnMouse(const std::pair<int, int>& pos) { return isOnMouse(pos.first, pos.second); };

	void setAlign(const Align::Horizontal& hAlign) { for (auto& btn: buttons) btn.setAlign(hAlign); };
	void setAlign(const Align::Vertical& vAlign) { for (auto& btn : buttons) btn.setAlign(vAlign); };
	void setAlign(const Align::Horizontal& hAlign, const Align::Vertical& vAlign) { for (auto& btn : buttons) btn.setAlign(hAlign, vAlign); };
	void setPosition(float x, float y) { for (auto& btn : buttons) btn.setPosition(std::make_pair(x, y)); };
	void setPosition(const Point& position) { for (auto& btn : buttons) btn.setPosition(position); };
	void setScale(float x, float y) { for (auto& btn : buttons) btn.setScale(x, y); };
	void setScale(const Point& scale) { for (auto& btn : buttons) btn.setScale(scale); };
	void setAlpha(int alpha) { for (auto& btn : buttons) btn.setAlpha(alpha); }; //0~255
protected:
	std::array<Image, static_cast<int>(State::INVALID)> buttons;

private:
	State nowState = State::NORMAL;
	const Panel* panel = nullptr;
};