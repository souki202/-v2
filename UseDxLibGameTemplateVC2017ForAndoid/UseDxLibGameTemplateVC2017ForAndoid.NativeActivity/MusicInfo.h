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
	MusicInfo(const std::string& filePath) { info.filePath = filePath; loadMusicInfo(filePath); };
	~MusicInfo() {};

	void loadMusicInfo(const std::string& filePath);
	const std::string& getFilePath() const { return info.filePath; };
private:
	Info info;
};