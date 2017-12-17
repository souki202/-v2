#pragma once
#include <fstream>
#include <sstream>
#include <memory>
#include <map>
#include "Timer.h"
#include "Note.h"
#include "GetFilePath.h"
#include "JudgeLine.h"
#include "MusicInfo.h"
#include <unordered_map>

#include "NormalNote.h"
#include "LongNote.h"
#include "SlideNote.h"
#include "FlickNote.h"
#include "Judge.h"
#include "Score.h"
#include "Combo.h"
#include "Life.h"
#include "ResultRecord.h"

class MusicScore {
public:
	MusicScore(const MusicInfo& musicInfo, int difficulty) 
		: musicInfo(musicInfo)
	{ loadMusicScore(difficulty); };
	MusicScore() {};
	~MusicScore() { DeleteSoundMem(bgm); };

	void setMusicInfo(const MusicInfo& musicInfo) { this->musicInfo = musicInfo; };
	void loadMusicScore(int difficulty);
	double calcElapsedTime(double lastPeriod, double nowPeriod, float bpm, int numBeatDiv, int beatDiv);
	
	void draw();
	void update();
	void startMusic() { PlaySoundMem(bgm, DX_PLAYTYPE_BACK); timer.reset(); isStarted = true; };
	bool isSurvive();
	//bool getIsEndMusic() { return !CheckSoundMem(bgm) && isStarted && endPlayTimer.getElapsedTime() > playSettings.getPlayEndWaitTime(); };
	bool getIsEndMusic() { return timer.getElapsedTime() > 10000; };
	void startMoveNotes() { noteDrawTimer.reset(); isStartMoveNotes = true; };
	void saveRecord();
	const ResultRecord& getResultRecord() const { return record; };
private:
	ResultRecord record;
	MusicInfo musicInfo;
	std::string filePath;
	float bpm = 1;
	Timer timer;
	Timer endPlayTimer;
	Timer noteDrawTimer;
	int bgm;
	bool isStartMoveNotes = false;

	Judge judge;
	Combo combo;
	Score score;
	Life life;

	std::vector<std::shared_ptr<Note>> notes;
	std::vector<std::string> errors;
	bool isStarted = false;
	int startDelayTime;
};