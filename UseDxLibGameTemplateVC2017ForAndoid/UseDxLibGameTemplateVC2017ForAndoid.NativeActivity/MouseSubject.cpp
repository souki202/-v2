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
		//�A�N�Z�X�ᔽ���Ȃ��悤,shared_ptr�ɑ�����Ă���.
		//���Ƀ}���`�X���b�h
		const auto& s = x.lock();
		if (s) {
			if (s->isOnMouse(e.pos)) {
				s->onMouse(e);
				//�N���b�N�͂���
				if (e.phases[0] == PressPhase::BEGAN
					|| e.phases[1] == PressPhase::BEGAN
					|| e.phases[2] == PressPhase::BEGAN) {
					s->onClick(e);
				}
				//�N���b�N��
				if (e.pressInfo[0].first > 0
					|| e.pressInfo[1].first > 0
					|| e.pressInfo[2].first > 0) {
					s->onPress(e);
					//������
					if (e.deltaPos.first || e.deltaPos.second) {
						s->onDrag(e);
					}
				}
				//�N���b�N�I���
				if (e.phases[0] == PressPhase::ENDED
					|| e.phases[1] == PressPhase::ENDED
					|| e.phases[2] == PressPhase::ENDED) {
					s->onRelease(e);
				}
			}
			else {
				//�O�͏���Ă���,����͗��ꂽ�ꍇ
				if (s->isOnMouse(e.pos.first - e.deltaPos.first, e.pos.second - e.deltaPos.second)) {
					if (!s->isOnMouse(e.pos)) {
						s->onLeave(e);
					}
				}
			}
		}
	}
}
