#include "TouchSubject.h"
#include "TouchListener.h"

void TouchSubject::update()
{
	const TouchEvent& e = *touchInput.getFirstTouch();
	using namespace InputDevice;
	for (auto& x : objs) {
		const auto& s = x.lock();
		if (s) {
			if (s->isOnTouch(e.nowPos)) {
				//クリックはじめ
				if (e.phase == PressPhase::BEGAN) {
					s->onTouch(e);
				}
				//クリック中
				if (e.frame > 0) {
					s->onHold(e);
					//動いた
					if (e.deltaPos.first || e.deltaPos.second) {
						s->onSlide(e);
					}
				}
				//クリック終わり
				if (e.phase == PressPhase::ENDED) {
					s->onRelease(e);
				}
			}
			else {
				//前は乗っていて,今回は離れた場合
				if (s->isOnTouch(e.nowPos.first - e.deltaPos.first, e.nowPos.second - e.deltaPos.second)) {
					if (!s->isOnTouch(e.nowPos)) {
						s->onLeave(e);
					}
				}
			}
		}
	}
}
