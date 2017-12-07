#pragma once
#include <fstream>
#include <sstream>
#include <memory>
#include <map>
#include "Note.h"
#include "GetFilePath.h"
#include "PlayPositions.h"

#include "NormalNote.h"
#include "LongNote.h"
#include "SlideNote.h"
#include "FlickNote.h"

class MusicScore {
public:
	MusicScore(const std::string& filePath) { loadMusicScore(filePath); };
	MusicScore() {};
	~MusicScore() {};

	void loadMusicScore(const std::string& filePath);
	double calcElapsedTime(double lastPeriod, double nowPeriod, float bpm, int numBeatDiv, int beatDiv);

	void draw();
	void update();
private:
	std::string filePath;
	float bpm;
	int startTime;

	std::vector<std::shared_ptr<Note>> notes;
	std::vector<std::string> errors;
};