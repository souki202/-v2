#pragma once
#include <string>
#include <array>
#include <fstream>
#include <sstream>
#include <cstdlib>

class MusicInfo {
private:
	struct Info {
		std::string filePath;
		std::string title;
		std::string artist;
		std::string genre;
		std::array<int, 3> difficulty;
	};
public:
	MusicInfo(const std::string& folderPath) { loadMusicInfo(folderPath); };
	MusicInfo() {};
	~MusicInfo() {};

	void loadMusicInfo(const std::string& folderPath);
	const std::string& getFilePath() const { return info.filePath; };//末尾にスラッシュが必ずつく
	const std::string& getTitle() const { return info.title; };
private:
	Info info;
};