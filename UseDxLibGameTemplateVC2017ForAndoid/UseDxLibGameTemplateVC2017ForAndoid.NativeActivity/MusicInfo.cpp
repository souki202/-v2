#include "MusicInfo.h"

void MusicInfo::loadMusicInfo(const std::string & folderPath)
{
	info.filePath = folderPath;
	if (info.filePath.back() != '/') info.filePath += '/';
	info.filePath = getExternalFilePath(info.filePath);
	std::ifstream ifs(info.filePath + "musicinfo.tsv");
	std::string line;
	coverPath = info.filePath + "title.png";
	int cnt = 0;
	while (std::getline(ifs, line)) {
		std::stringstream ss(line);
		std::string value;
		while (std::getline(ss, value, '\t')) {
			switch (cnt)
			{
			case 0: info.title = value; break;
			case 1: info.artist = value; break;
			case 2: info.genre = value; break;
			case 3: case 4: case 5: case 6: case 7: case 8:
				info.difficulty[cnt - 3] = std::atoi(value.c_str());
				break;
			case 9:  coverPath = info.filePath + value; break;
			}
			cnt++;
		}
	}
}

const Image & MusicInfo::getCover()
{
	return info.cover;
}
