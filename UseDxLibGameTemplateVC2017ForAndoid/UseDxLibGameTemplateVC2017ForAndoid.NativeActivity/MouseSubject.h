#pragma once
#include <memory>
#include "Subject.h"
#include "InputDevice.h"

class MouseListener;

class MouseSubject : virtual public Subject<MouseListener> {
public:
	MouseSubject() {};
	virtual ~MouseSubject() {};

	void update();
private:
};