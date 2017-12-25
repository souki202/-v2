#pragma once
#include "DxLib.h"
#include "CommonSettings.h"
#include "InputDevice.h"
#include "Factory.h"
#include "SelectMusic.h"
#include "Result.h"
#include <unistd.h>
#include <unwind.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "NoteCommon.h"
#include "Timer.h"

class Form
{
public:
	Form();
	~Form();

	bool update();
	bool draw();
private:
	Timer timer;
};
//---------------------------------------------------------------------------