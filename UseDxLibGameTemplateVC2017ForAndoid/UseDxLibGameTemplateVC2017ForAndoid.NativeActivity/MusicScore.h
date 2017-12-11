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

#include "NormalNote.h"
#include "LongNote.h"
#include "SlideNote.h"
#include "FlickNote.h"
#include "Judge.h"
#include "Score.h"
#include "Combo.h"


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
	void startMusic() { PlaySoundMem(bgm, DX_PLAYTYPE_BACK); timer.reset(); };
private:
	MusicInfo musicInfo;
	std::string filePath;
	float bpm = 1;
	int startTime;
	Timer timer;
	int bgm;

	Judge judge;
	Combo combo;
	Score score;

	std::vector<std::shared_ptr<Note>> notes;
	std::vector<std::string> errors;

};