#pragma once
#include "JudgeGrade.h"

struct JudgeResult {
	JudgeGrade grade = JudgeGrade::INVALID;
	int id = -1;
};