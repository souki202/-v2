#pragma once
#include <utility>
typedef std::pair<float, float> Point;

namespace Align {
	enum class Horizontal {
		LEFT, CENTER, RIGHT, INVALID,
	};

	enum class Vertical {
		UPPER, MIDDLE, BOTTOM, INVALID,
	};

	static Point calcBasePosition(const Point& leftUpperPos, const Point& size, const Horizontal& hAlign, const Vertical& vAlign) {
		Point newPos = leftUpperPos;

		switch (hAlign)
		{
		case Align::Horizontal::LEFT:
			break;
		case Align::Horizontal::CENTER:
			newPos.first -= size.first / 2;
			break;
		case Align::Horizontal::RIGHT:
			newPos.first -= size.first;
			break;
		case Align::Horizontal::INVALID:
			break;
		default:
			break;
		}

		switch (vAlign)
		{
		case Align::Vertical::UPPER:
			break;
		case Align::Vertical::MIDDLE:
			newPos.second -= size.second / 2;
			break;
		case Align::Vertical::BOTTOM:
			newPos.second -= size.second;
			break;
		case Align::Vertical::INVALID:
			break;
		default:
			break;
		}

		return newPos;
	}
};