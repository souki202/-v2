#include "ResultThumb.h"

ResultThumb::ResultThumb()
{

}

ResultThumb::ResultThumb(const std::string & cover)
{
	setCover(cover);
}

void ResultThumb::setCover(const std::string & cover)
{
	this->cover.setImage(cover);
	this->cover.setAlign(Align::Horizontal::CENTER, Align::Vertical::MIDDLE);
	this->cover.setPosition(883.f, 518.f);
}

void ResultThumb::calcScale()
{
	float scale = MyFuncs::calcScaleInWindow(this->cover.getSize().first, this->cover.getSize().second, 346.f, 346.f);
	cover.setScale(scale, scale);
}
