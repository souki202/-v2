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
				//�N���b�N�͂���
				if (e.phase == PressPhase::BEGAN) {
					s->onTouch(e);
				}
				//�N���b�N��
				if (e.frame > 0) {
					s->onHold(e);
					//������
					if (e.deltaPos.first || e.deltaPos.second) {
						s->onSlide(e);
					}
				}
				//�N���b�N�I���
				if (e.phase == PressPhase::ENDED) {
					s->onRelease(e);
				}
			}
			else {
				//�O�͏���Ă���,����͗��ꂽ�ꍇ
				if (s->isOnTouch(e.nowPos.first - e.deltaPos.first, e.nowPos.second - e.deltaPos.second)) {
					if (!s->isOnTouch(e.nowPos)) {
						s->onLeave(e);
					}
				}
			}
		}
	}
}
