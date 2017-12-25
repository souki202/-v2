#pragma once
#include "MouseEvent.h"

struct ButtonEvent {
	ButtonEvent(const MouseEvent& e) {
		mouseEvent = e;
	};
	MouseEvent mouseEvent;
};