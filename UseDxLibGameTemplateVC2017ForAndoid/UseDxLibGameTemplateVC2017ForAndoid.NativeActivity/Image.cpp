#include "Image.h"

Image::Image()
{
	alpha = 255;
}

Image::Image(std::string filePath)
{
	setImage(filePath);
	setPosition(std::make_pair(0.f, 0.f));
	init();
}

Image::Image(std::string filePath, const Align::pos_type & position)
{
	setImage(filePath);
	setPosition(position);
	init();
}

Image::Image(int handle)
{
	setImage(handle);
	setPosition(std::make_pair(0.f, 0.f));
	init();
}

Image::Image(int handle, const Align::pos_type & position)
{
	setImage(handle);
	setPosition(position);
	init();
}

Image::~Image()
{
	if (!isExternal) DeleteGraph(img);
}

void Image::init()
{
	alpha = 255;
}

void Image::setAlign(const Align::Horizontal & hAlign, const Align::Vertical & vAlign)
{
	this->hAlign = hAlign;
	this->vAlign = vAlign;
	recalcPosition();
}

void Image::setImage(std::string filePath)
{
	img = LoadGraph(filePath.c_str());
	GetGraphSizeF(img, &rawSize.first, &rawSize.second);
	recalcPosition();
}

void Image::setImage(int handle)
{
	img = handle;
	GetGraphSizeF(img, &rawSize.first, &rawSize.second);
	recalcPosition();
	isExternal = true;
}

void Image::setPosition(const Align::pos_type & position)
{
	rawPos = position;
	recalcPosition();
}

void Image::setScrollPosition(const Align::pos_type & scroll)
{
	scrollPos = scroll;
	recalcPosition();
}

void Image::setScale(const Align::pos_type & scale)
{
	this->scale = scale;
	recalcPosition();
}

void Image::setAngle(float angle)
{
	this->angle = angle;
	recalcPosition();
}

void Image::recalcPosition()
{
	scaledSize.first = rawSize.first * scale.first;
	scaledSize.second = rawSize.second * scale.second;
	pos = Align::calcBasePosition(rawPos, scaledSize, hAlign, vAlign);
	pos.first += scrollPos.first;
	pos.second += scrollPos.second;

	//回転
	float x[2], y[2]; //0:左上 1:右下
	x[0] = pos.first - rawPos.first;
	x[1] = x[0] + scaledSize.first;
	y[0] = pos.second - rawPos.second;
	y[1] = y[0] + scaledSize.second;
	float s = std::sin(angle);
	float c = std::cos(angle);
	vertexes[0].first = x[0] * c - y[0] * s;//左上
	vertexes[0].second = x[0] * s + y[0] * c;
	vertexes[1].first = x[1] * c - y[0] * s;//右上
	vertexes[1].second = x[1] * s + y[0] * c;
	vertexes[2].first = x[1] * c - y[1] * s;//右下
	vertexes[2].second = x[1] * s + y[1] * c;
	vertexes[3].first = x[0] * c - y[1] * s;//左下
	vertexes[3].second = x[0] * s + y[1] * c;

	for (auto& x : vertexes) {
		x.first += rawPos.first;
		x.second += rawPos.second;
	}
}

void Image::draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawModiGraphF(
		vertexes[0].first, vertexes[0].second,
		vertexes[1].first, vertexes[1].second,
		vertexes[2].first, vertexes[2].second,
		vertexes[3].first, vertexes[3].second,
		img, true
	);
	//DrawExtendGraphF(pos.first, pos.second, pos.first + scaledSize.first, pos.second + scaledSize.second, img, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Image::update()
{
}

bool Image::getIsOutOfWindow()
{
	//いずれかの点が画面内なら映っている
	bool isOk = false;
	for (auto& x : vertexes) {
		if (0 < x.first) {
			isOk = false;
		}
	}
	if (isOk) return true;

	for (auto& x : vertexes) {
		if (x.first < CommonSettings::WINDOW_WIDTH) {
			isOk = false;
		}
	}
	if (isOk) return true;

	for (auto& x : vertexes) {
		if (0 < x.second) {
			isOk = false;
		}
	}
	if (isOk) return true;

	for (auto& x : vertexes) {
		if (x.second < CommonSettings::WINDOW_HEIGHT) {
			isOk = false;
		}
	}
	if (isOk) return true;

	return false;
}
