#pragma once
#include <utility>

namespace Align {
	typedef std::pair<float, float> pos_type;
	enum class Horizontal {
		LEFT, CENTER, RIGHT, INVALID,
	};

	enum class Vertical {
		UPPER, MIDDLE, BOTTOM, INVALID,
	};

	static pos_type calcBasePosition(const pos_type& leftUpperPos, const pos_type& size, const Horizontal& hAlign, const Vertical& vAlign) {
		pos_type newPos = leftUpperPos;

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