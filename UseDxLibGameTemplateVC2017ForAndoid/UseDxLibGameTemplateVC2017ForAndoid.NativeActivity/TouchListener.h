#pragma once
#include "HaveUuid.h"
#include "TouchEvent.h"

class TouchListener {
public:
	TouchListener() {};
	virtual ~TouchListener() {};

	/**
	* タップした瞬間のみ.
	*/
	virtual void onTouch(const TouchEvent& e) {};

	/**
	* onTouchが前提 押している間ずっと.
	*/
	virtual void onHold(const TouchEvent& e) {};

	/**
	* onTouchとonHoldが前提 タッチ位置が移動しているときのみ.
	*/
	virtual void onSlide(const TouchEvent& e) {};

	/**
	* タッチを終了した瞬間のみ.
	*/
	virtual void onRelease(const TouchEvent& e) {};

	/**
	* onTapが前提 タッチが離れた瞬間のみ.
	*/
	virtual void onLeave(const TouchEvent& e) {};

	virtual bool isOnTouch(int x, int y) {
		return leftUp.first <= x && x <= rightBottom.first
			&& leftUp.second <= y && y <= rightBottom.second;
	};
	virtual bool isOnTouch(const std::pair<int, int>& pos) {
		return isOnTouch(pos.first, pos.second);
	};

	virtual void setArea(const std::pair<int, int>& leftUp, const std::pair<int, int>& rightBottom) {
		this->leftUp = leftUp;
		this->rightBottom = rightBottom;
	}
private:
	std::pair<int, int> leftUp; //first:x second:y
	std::pair<int, int> rightBottom; //first:x second:y
};