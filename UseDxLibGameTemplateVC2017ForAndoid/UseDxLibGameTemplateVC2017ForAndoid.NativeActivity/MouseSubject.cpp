#include "MouseSubject.h"
#include "MouseListener.h"

void MouseSubject::update()
{
	MouseEvent e;
	e.pos = mouseInput.getPosition();
	e.deltaPos = mouseInput.getDeltaPosition();
	e.pressInfo = mouseInput.getPressInfo();
	e.phases = mouseInput.getPhaseInfo();
	
	using namespace InputDevice;
	for (auto& x : objs) {
		//アクセス違反がないよう,shared_ptrに代入してから.
		//特にマルチスレッド
		const auto& s = x.lock();
		if (s) {
			if (s->isOnMouse(e.pos)) {
				s->onMouse(e);
				//クリックはじめ
				if (e.phases[0] == PressPhase::BEGAN
					|| e.phases[1] == PressPhase::BEGAN
					|| e.phases[2] == PressPhase::BEGAN) {
					s->onClick(e);
				}
				//クリック中
				if (e.pressInfo[0].first > 0
					|| e.pressInfo[1].first > 0
					|| e.pressInfo[2].first > 0) {
					s->onPress(e);
					//動いた
					if (e.deltaPos.first || e.deltaPos.second) {
						s->onDrag(e);
					}
				}
				//クリック終わり
				if (e.phases[0] == PressPhase::ENDED
					|| e.phases[1] == PressPhase::ENDED
					|| e.phases[2] == PressPhase::ENDED) {
					s->onRelease(e);
				}
			}
			else {
				//前は乗っていて,今回は離れた場合
				if (s->isOnMouse(e.pos.first - e.deltaPos.first, e.pos.second - e.deltaPos.second)) {
					if (!s->isOnMouse(e.pos)) {
						s->onLeave(e);
					}
				}
			}
		}
	}
}
