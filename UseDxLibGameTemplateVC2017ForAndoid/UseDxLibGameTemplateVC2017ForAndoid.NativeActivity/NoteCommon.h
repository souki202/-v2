#pragma once
#include <array>
#include "DxLib.h"

#define noteImageManager NoteImageManager::getInstance()

enum class NoteType {
	NONE, NORMAL, 
	LN, SLIDE, SLIDE_RELAY ,
	FLICK_L, FLICK_R, //LRÇÕLNÇ∆SLIDEèIì_à»äOñ≥éã
	INVALID
};

enum class JudgeTiming {
	TOUCH, FLICK_L, FLICK_R, RELEASE_INIT, RELEASE, THROUGH, INVALID
};

class NoteImageManager {
private:
	NoteImageManager() {};
	~NoteImageManager() {};

	static std::array<int, static_cast<int>(NoteType::INVALID)> noteImg;
public:
	static const NoteImageManager& getInstance() { static NoteImageManager n; return n; };

	static void loadImage();
	static void releaseImage() {
		for (int i = 0; i < static_cast<int>(NoteType::INVALID); i++) {
			DeleteGraph(noteImg[i]);
		}
	}
	static const int& getNoteImage(const NoteType& type) { return noteImg[static_cast<int>(type)]; };
private:

};
