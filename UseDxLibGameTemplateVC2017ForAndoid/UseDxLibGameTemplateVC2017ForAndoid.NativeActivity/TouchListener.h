#pragma once
#include "HaveUuid.h"
#include "TouchEvent.h"

class TouchListener {
public:
	TouchListener() {};
	virtual ~TouchListener() {};

	/**
	* �^�b�v�����u�Ԃ̂�.
	*/
	virtual void onTouch(const TouchEvent& e) {};

	/**
	* onTouch���O�� �����Ă���Ԃ�����.
	*/
	virtual void onHold(const TouchEvent& e) {};

	/**
	* onTouch��onHold���O�� �^�b�`�ʒu���ړ����Ă���Ƃ��̂�.
	*/
	virtual void onSlide(const TouchEvent& e) {};

	/**
	* �^�b�`���I�������u�Ԃ̂�.
	*/
	virtual void onRelease(const TouchEvent& e) {};

	/**
	* onTap���O�� �^�b�`�����ꂽ�u�Ԃ̂�.
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