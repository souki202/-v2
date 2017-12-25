#pragma once
#include <map>
#include <vector>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <memory>
#include "MouseSubject.h"
#include "MouseEvent.h"
#include "TouchEvent.h"
#include "InputDevice.h"

//1つ目のタッチはマウスの左クリック扱いにする
#define IS_SIMULATE_TOUCH

/**
 * パネル管理クラス.
 * 重なり順を考慮する.
 */
template <typename T>
class LayerObject {
public:
	enum class PanelMouseState {
		ON_PANEL, OUT_PANEL, INVALID,
	};
	using PanelStateType = std::pair<std::weak_ptr<T>, PanelMouseState>;
	using LayerStateType = std::vector<PanelStateType>;

	LayerObject() { invalidUuid = boost::uuids::random_generator()(); outPanelUuid = boost::uuids::random_generator()(); };
	~LayerObject() {};

	int addObject(const std::shared_ptr<T>& panel); //常に最前面に挿入
	void removeObject(const boost::uuids::uuid& uuid);
	int changeActive(const boost::uuids::uuid& uuid);
	std::shared_ptr<T> searchObject(const boost::uuids::uuid& uuid);

	void update();
	void draw();
private:
	enum class InputMode {
		MOUSE, TOUCH, INVALID
	};
	std::map<int, LayerStateType> p; //z, panel
	boost::uuids::uuid holdUuid, invalidUuid, outPanelUuid;
	MouseEvent e;
	InputMode inputMode = InputMode::MOUSE;
};


template<typename T>
int LayerObject<T>::addObject(const std::shared_ptr<T>& panel)
{
	//アクティブになるようなzを計算
	int activeZ = 0;
	if (!p.empty()) {
		activeZ = p.rbegin()->first + 1;
	}

	//最前面に入れる
	if (!p.count(activeZ)) p[activeZ] = LayerStateType();
	p[activeZ].push_back(std::make_pair(panel, PanelMouseState::OUT_PANEL));
	return activeZ;
}

template<typename T>
void LayerObject<T>::removeObject(const boost::uuids::uuid & uuid)
{
	bool isOk = false;
	for (auto it = p.begin(); it != p.end();) {
		for (auto it2 = it->second.begin(); it2 != it->second.end();) {
			auto s = it2->first.lock();
			if (!s || (s && s->getUuid() == uuid)) {
				it2 = it->second.erase(it2);
				isOk = true;
				break;
			}
			else ++it2;
		}
		if (isOk) {
			if (it->second.empty()) it = p.erase(it);
			else ++it;
			return;
		}
		else ++it;
	}
}

template<typename T>
int LayerObject<T>::changeActive(const boost::uuids::uuid & uuid)
{
	//今入っているのを削除
	std::shared_ptr<T> target;
	target = searchObject(uuid);
	removeObject(uuid);
	return addObject(target);
}

template<typename T>
std::shared_ptr<T> LayerObject<T>::searchObject(const boost::uuids::uuid & uuid)
{
	for (auto it = p.begin(); it != p.end(); ++it) {
		for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
			auto& s = it2->first.lock();
			if (s && s->getUuid() == uuid) {
				return s;
			}
		}
	}
	return nullptr;
}

template<typename T>
inline void LayerObject<T>::update()
{
	using namespace InputDevice;
	PanelStateType* lastOnPanel = nullptr;
	PanelStateType* nowOnPanel = nullptr;

	bool isClick = false;

#ifdef IS_SIMULATE_TOUCH
	//タッチを優先する.
	const TouchEvent* te = touchInput.getFirstTouch();
	if (te != nullptr) {
		int button = te->time > 750 ? 1 : 0;
		e.pos = te->nowPos;
		e.deltaPos = te->deltaPos;
		e.pressInfo[button] = std::make_pair(te->frame, te->time);
		e.phases[button] = te->phase;
		inputMode = InputMode::TOUCH;
	}
	else if (inputMode == InputMode::TOUCH) { //タッチしていないがマウスを使っていない
		e.pressInfo = {std::make_pair(0, 0), std::make_pair(0, 0), std::make_pair(0, 0)};
		e.phases = {PressPhase::INVALID, PressPhase::INVALID, PressPhase::INVALID};
	}
	else {
		if (mouseInput.getDeltaPosition().first != 0 || mouseInput.getDeltaPosition().second || isClick
			|| inputMode == InputMode::MOUSE) {
			e.pos = mouseInput.getPosition();
			e.deltaPos = mouseInput.getDeltaPosition();
			e.pressInfo = mouseInput.getPressInfo();
			e.phases = mouseInput.getPhaseInfo();
			inputMode = InputMode::MOUSE;
		}
	}
#else
	e.pos = mouseInput.getPosition();
	e.deltaPos = mouseInput.getDeltaPosition();
	e.pressInfo = mouseInput.getPressInfo();
	e.phases = mouseInput.getPhaseInfo();
#endif
	isClick = e.pressInfo[0].first > 0 || e.pressInfo[1].first > 0 || e.pressInfo[2].first > 0;


	//クリックしていなければUUIDのホールドを解除
	if (!isClick) {
		holdUuid = invalidUuid;
	}
	//前回乗っていたパネルを探す
	for (auto it = p.rbegin(); it != p.rend() && lastOnPanel == nullptr; ++it) {
		for (auto& y : it->second) {
			auto s = y.first.lock();
			if (s) {
				if (s->isOnMouse(e.pos.first - e.deltaPos.first, e.pos.second - e.deltaPos.second)) {
					lastOnPanel = &y;
					break;
				}
			}
		}
	}
	
	for (auto it = p.rbegin(); it != p.rend() && nowOnPanel == nullptr; ++it) {
		//マウスイベント発行
		for (auto& y : it->second) {
			//アクセス違反がないよう,shared_ptrに代入してから.
			//特にマルチスレッド
			auto s = y.first.lock();
			if (s) {
				//ホールドuuidチェック
				if (!(holdUuid == invalidUuid || s->getUuid() == holdUuid)) {
					continue;
				}
				if (s->isOnMouse(e.pos)) {
					//前回と乗っているパネルが違うなら,前回のパネルにLeaveイベントを起こす
					if (lastOnPanel != nullptr) {
						auto l = lastOnPanel->first.lock();
						if (l && l->getUuid() != s->getUuid()) {
							l->onLeave(e);
							lastOnPanel->second = PanelMouseState::OUT_PANEL;
						}
					}
					y.second = PanelMouseState::ON_PANEL;
					nowOnPanel = &y;
					holdUuid = s->getUuid();
					if (inputMode == InputMode::MOUSE) {
						s->onMouse(e);
					}
					//クリックはじめ
					if (e.phases[0] == PressPhase::BEGAN
						|| e.phases[1] == PressPhase::BEGAN
						|| e.phases[2] == PressPhase::BEGAN) {
						s->onClick(e);
					}
					//クリック中
					if (isClick) {
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

					break;
				}
			}
		}
	}
	//どのパネルにも乗ってないなら,前回のパネルにLeaveイベントを起こす
	if (nowOnPanel == nullptr && lastOnPanel != nullptr) {
		auto l = lastOnPanel->first.lock();
		if (l) {
			l->onLeave(e);
			lastOnPanel->second = PanelMouseState::OUT_PANEL;
		}
	}
	//どこでもない場所をクリック
	if (nowOnPanel == nullptr && isClick && holdUuid == invalidUuid) {
		holdUuid = outPanelUuid;
	}
	for (auto& x : p) {
		for (auto& y : x.second) {
			auto s = y.first.lock();
			if (s) s->update();
		}
	}
}

template<typename T>
inline void LayerObject<T>::draw()
{
	for (auto& x : p) {
		for (auto& y : x.second) {
			auto& s = y.first.lock();
			if (s) s->draw();
		}
	}
}
