#pragma once
#include "HaveUuid.h"
#include "MouseEvent.h"

class MouseListener {
public:
	MouseListener() {};
	virtual ~MouseListener() {};

	/**
	 * マウスポインタが乗っていれば発行される.
	 */
	virtual void onMouse(const MouseEvent& e) {};

	/**
	 * onMouseが前提 押した瞬間のみ.
	 * 左,右,中のどれかでも押した瞬間なら発行されるのでチェックするように.
	 */
	virtual void onClick(const MouseEvent& e) {};

	/**
	 * onMouseが前提 押している間ずっと.
	 * 左,右,中のどれかでも押した瞬間なら発行されるのでチェックするように.
	 */
	virtual void onPress(const MouseEvent& e) {};

	/**
	 * onMouseとonPressが前提 マウスが移動しているときのみ.
	 * 左,右,中のどれかでも押した瞬間なら発行されるのでチェックするように.
	 */
	virtual void onDrag(const MouseEvent& e) {};

	/**
	 * onMouseが前提 マウスを離した瞬間のみ.
	 * 左,右,中のどれかでも押した瞬間なら発行されるのでチェックするように.
	 */
	virtual void onRelease(const MouseEvent& e) {};

	/**
	 * onMouseが前提 マウスオーバーから離れた瞬間のみ.
	 */
	virtual void onLeave(const MouseEvent& e) {};

	virtual bool isOnMouse(int x, int y) {
		return leftUp.first <= x && x <= rightBottom.first
			&& leftUp.second <= y && y <= rightBottom.second;
	};
	virtual bool isOnMouse(const std::pair<int, int>& pos) {
		return isOnMouse(pos.first, pos.second);
	};

	virtual void setArea(const std::pair<int, int>& leftUp, const std::pair<int, int>& rightBottom) {
		this->leftUp = leftUp;
		this->rightBottom = rightBottom;
	}
private:
	std::pair<int, int> leftUp; //first:x second:y
	std::pair<int, int> rightBottom; //first:x second:y
};