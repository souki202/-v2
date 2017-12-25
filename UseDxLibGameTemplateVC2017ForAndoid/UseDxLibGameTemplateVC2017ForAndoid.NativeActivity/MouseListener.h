#pragma once
#include "HaveUuid.h"
#include "MouseEvent.h"

class MouseListener {
public:
	MouseListener() {};
	virtual ~MouseListener() {};

	/**
	 * �}�E�X�|�C���^������Ă���Δ��s�����.
	 */
	virtual void onMouse(const MouseEvent& e) {};

	/**
	 * onMouse���O�� �������u�Ԃ̂�.
	 * ��,�E,���̂ǂꂩ�ł��������u�ԂȂ甭�s�����̂Ń`�F�b�N����悤��.
	 */
	virtual void onClick(const MouseEvent& e) {};

	/**
	 * onMouse���O�� �����Ă���Ԃ�����.
	 * ��,�E,���̂ǂꂩ�ł��������u�ԂȂ甭�s�����̂Ń`�F�b�N����悤��.
	 */
	virtual void onPress(const MouseEvent& e) {};

	/**
	 * onMouse��onPress���O�� �}�E�X���ړ����Ă���Ƃ��̂�.
	 * ��,�E,���̂ǂꂩ�ł��������u�ԂȂ甭�s�����̂Ń`�F�b�N����悤��.
	 */
	virtual void onDrag(const MouseEvent& e) {};

	/**
	 * onMouse���O�� �}�E�X�𗣂����u�Ԃ̂�.
	 * ��,�E,���̂ǂꂩ�ł��������u�ԂȂ甭�s�����̂Ń`�F�b�N����悤��.
	 */
	virtual void onRelease(const MouseEvent& e) {};

	/**
	 * onMouse���O�� �}�E�X�I�[�o�[���痣�ꂽ�u�Ԃ̂�.
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