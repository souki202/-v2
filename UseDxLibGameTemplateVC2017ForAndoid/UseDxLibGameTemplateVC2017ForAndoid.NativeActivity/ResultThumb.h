#pragma once
#include "Image.h"
#include "MusicInfo.h"
#include "MyFuncs.h"

class ResultThumb {
public:
	ResultThumb();
	ResultThumb(const std::string& cover);
	~ResultThumb() {};

	void draw() { cover.draw(); };
	void update() {};
	void setCover(const std::string& cover);
	void calcScale();
private:
	Image cover;

};