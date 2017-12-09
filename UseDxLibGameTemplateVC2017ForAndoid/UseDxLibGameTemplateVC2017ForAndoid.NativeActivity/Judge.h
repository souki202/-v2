#pragma once
#include <vector>
#include <array>
#include "NoteCommon.h"
#include "JudgeGrade.h"
#include "InputDevice.h"
#include "JudgeResult.h"

class Judge {
public:
	Judge() { setJudgeDifficulty(1); };
	~Judge() {};

	void setJudgeDifficulty(int difficulty);
	void resetJudgedId() { judgedId.clear(); };
	JudgeResult judge(const JudgeTiming& timing, int nowTime, int judgeTime, int line, int touchId);
	JudgeGrade calcGrade(int deltaTime, bool isInLn = false);

	int searchUnuseId(const InputDevice::TouchMap& touches, int line); //ˆ—Ï‚İ‚©’†g‚È‚µ‚È‚ç-1

	void draw();
private:
	std::vector<int> judgedId;//”»’èÏ‚İ‚Ìid‚ğŠi”[
	std::array<int, static_cast<int>(JudgeGrade::INVALID)> judgeRange;

	int lastJudgeStr = -1;
};