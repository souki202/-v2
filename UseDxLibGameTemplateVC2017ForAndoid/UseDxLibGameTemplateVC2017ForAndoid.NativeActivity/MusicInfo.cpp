#include "MusicInfo.h"

void MusicInfo::loadMusicInfo(const std::string & folderPath)
{
	info.filePath = folderPath;
	if (info.filePath.back() != '/') info.filePath += '/';
	info.filePath = getExternalFilePath(info.filePath);
	std::ifstream ifs(info.filePath + "musicinfo.tsv");
	std::string line;
	bool isFirstLine = true;
	while (std::getline(ifs, line)) {
		if (!isFirstLine) break;
		isFirstLine = false;

		std::stringstream ss(line);
		int cnt = 0;
		while (std::getline(ss, line, '\t')) {
			switch (cnt)
			{
			case 0: info.title = line; break;
			case 1: info.artist = line; break;
			case 2: info.genre = line; break;
			case 3: case 4: case 5: info.difficulty[cnt - 3] = std::atoi(line.c_str()); break;
			}
			cnt++;
		}
	}
}
