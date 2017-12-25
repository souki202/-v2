#pragma once
#include <boost/signals.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/function.hpp>
#include <functional>
#include <map>
#include "ButtonEvent.h"
#include "MouseSubject.h"

using EventFuncType = boost::function<void(const ButtonEvent&)>;

class ButtonSubject : virtual public MouseSubject {
public:
	ButtonSubject() : MouseSubject() {};
	virtual ~ButtonSubject() {};

	//virtual void addFunction(EventFuncType func) { funcs.connect(func); };
	//virtual void removeFunction(EventFuncType func) { funcs.disconnect(func); };
	virtual void call(const ButtonEvent& e) { funcs(e); };
public:
	boost::signals2::signal<void (const ButtonEvent&)> funcs;

private:
};