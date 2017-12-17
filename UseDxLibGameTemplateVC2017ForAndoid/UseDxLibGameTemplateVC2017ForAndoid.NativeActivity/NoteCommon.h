#pragma once
#include <array>
#include "Image.h"
#include "DxLib.h"

#define noteImageManager NoteImageManager::getInstance()

enum class NoteType {
	NONE, NORMAL, 
	LN, SLIDE, SLIDE_RELAY ,
	FLICK_L, FLICK_R, //LRはLNとSLIDE終点以外無視
	INVALID
};

enum class JudgeTiming {
	TOUCH, FLICK_L, FLICK_R, RELEASE_INIT, RELEASE, THROUGH, INVALID
};

class NoteImageManager {
private:
	NoteImageManager() {};
	~NoteImageManager() {};

	std::array<int, static_cast<int>(NoteType::INVALID)> noteImg;
	std::array<std::array<int, static_cast<int>(NoteType::INVALID)>, 4> familyNoteImg;
	int* rawFamilyNoteImg = nullptr;
	Image whiteImg;
	Image connectImg;
public:
	static NoteImageManager& getInstance() { static NoteImageManager n; return n; };

	void loadImage();
	void releaseImage() {
		for (int i = 0; i < static_cast<int>(NoteType::INVALID); i++) {
			DeleteGraph(noteImg[i]);
		}
	}
	const int& getNoteImage(const NoteType& type) const { return familyNoteImg[3][static_cast<int>(type)]; };
	const Image& getWhiteImage() const { return whiteImg; };
	int getConnectImage() const { return connectImg.getHandle(); };
private:

};
