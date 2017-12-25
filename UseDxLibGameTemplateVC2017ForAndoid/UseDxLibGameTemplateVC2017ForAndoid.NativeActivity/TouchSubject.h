#pragma once
#include <memory>
#include "Subject.h"
#include "InputDevice.h"

class TouchListener;

class TouchSubject : virtual public Subject<TouchListener> {
public:
	TouchSubject() {};
	virtual ~TouchSubject() {};

	void update();
private:
};