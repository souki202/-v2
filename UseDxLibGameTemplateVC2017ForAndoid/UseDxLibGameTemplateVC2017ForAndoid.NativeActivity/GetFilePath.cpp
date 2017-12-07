#include "GetFilePath.h"

std::string getExternalFilePath(const std::string & filePath)
{
	char cfilePath[512];
	GetExternalDataPath(cfilePath, 511);
	return cfilePath + std::string("/") + filePath;
}
