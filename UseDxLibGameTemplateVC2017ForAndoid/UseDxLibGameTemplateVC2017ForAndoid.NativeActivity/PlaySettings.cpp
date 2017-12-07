#include "PlaySettings.h"

void PlaySettings::loadConfig()
{
	std::string filePath = getExternalFilePath("Assets/Musics/playSetting.txt");
	std::ifstream ifs(filePath);
	std::string line;
	int cnt = 0;
	while (std::getline(ifs, line)) {
		switch (cnt)
		{
		case 0: hiSpeed = std::atoi(line.c_str());
		}
		cnt++;
	}
}
