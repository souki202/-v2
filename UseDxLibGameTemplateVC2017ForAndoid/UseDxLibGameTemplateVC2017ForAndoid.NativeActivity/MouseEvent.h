#pragma once
#include <utility>
#include "InputDevice.h"

enum class MouseButton {
	LEFT, RIGHT, CENTER, INVALID,
};

struct MouseEvent {
	std::pair<int, int> pos;
	std::pair<int, int> deltaPos;

	/**
	 * [0]:LEFT [1]:RIGHT [2]:MIDDLE
	 * first:frame second:realtime (deltatime�̐ςݏグ�Ȃ̂Ō덷���ςݏオ��)
	 */
	std::array<std::pair<int, int>, 3> pressInfo;

	/**
	 * [0]:LEFT [1]:RIGHT [2]:MIDDLE
	*/
	std::array<InputDevice::PressPhase, 3> phases;
};