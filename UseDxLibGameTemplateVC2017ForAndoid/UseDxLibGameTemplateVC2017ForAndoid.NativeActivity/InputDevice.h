#pragma once
//----------------------------------------------------------
#define _USE_MATH_DEFINES
#include <array>
#include <map>
#include <cmath>
#include <algorithm>
#include <vector>
#include "DxLib.h"
#include "Timer.h"
#include "CommonSettings.h"
#include "JudgeLine.h"
#include "FlickDirection.h"

#define USE_INPUTDEVICE_DEF

#ifdef USE_INPUTDEVICE_DEF
#define keyInput InputDevice::Keyboard::getInstance()
#define mouseInput InputDevice::Mouse::getInstance()
#define touchInput InputDevice::DeresutePlayTouchInput::getInstance2()
#endif

//----------------------------------------------------------
namespace InputDevice {
	enum PressPhase {
		BEGAN, IN_THE_MIDDLE, ENDED, INVALID
	};
	typedef std::map<int, std::vector<int>> TouchMap; //line, id

	class Keyboard {
	private:
		Keyboard();
		~Keyboard();
	public:
		static Keyboard& getInstance() { static Keyboard key; return key; };

		void update();				// キーの入力状態を更新する
		int getPressFrame(int keyCode) { return m_frame[keyCode]; }// 引数のキーコードのキーの入力フレーム数を返す
		int getPressTime(int keyCode) { return m_time[keyCode]; }	// 引数のキーコードのキーの入力時間(リアルタイム)を返す
		bool isRelease(int keyCode);	// ボタンが上がったとき
		void setInterval(int time) { m_interval = time; };	//ミリ秒
		bool getIsUpdate(int keyCode);	//フレーム基準なら余り求めてね★
	private:
		Timer timer;
		std::array<int, 256> m_frame;
		std::array<int, 256> m_time;
		std::array<int, 256> m_lastUpdateTime;
		std::array<bool, 256> m_isPress;
		char m_isPushKey[256];	//Update()でキーの入力状態を保持

		int m_interval;
	};

	class Mouse {
	private:
		Mouse();
		~Mouse();

	public:
		static Mouse& getInstance() { static Mouse mouse; return mouse; };

		void update();
		int getLeftPressFrame() { return press[0].first; };
		int getLeftPressTime() { return press[0].second; };
		int getLeftPressPhase() { return phases[0]; };
		const std::pair<int, int>& getLeftClickInitPosition() { return m_leftClickInitPosition; };
		int getRightPressFrame() { return press[1].first; };
		int getRightPressTime() { return press[1].second; };
		int getRightPressPhase() { return phases[1]; };
		int getMiddlePressFrame() { return press[2].first; };
		int getMiddlePressTime() { return press[2].second; };
		int getMiddlePressPhase() { return phases[2]; };
		int getWheelRotateValue() { return GetMouseWheelRotVol(); };	//奥が正, 手前が負
		const std::pair<int, int>& getPosition() {
			return m_position;
		};
		std::pair<int, int> getDeltaPosition() {
			return std::make_pair(m_position.first - m_lastPosition.first, m_position.second - m_lastPosition.second);
		};

		const std::array<std::pair<int, int>, 3>& getPressInfo() const { return press; };
		const std::array<PressPhase, 3>& getPhaseInfo() const { return phases; };
	private:
		Timer timer;
		std::array<std::pair<int, int>, 3> press;//フレーム, 時間
		std::pair<int, int> m_position;
		std::pair<int, int> m_leftClickInitPosition;
		std::pair<int, int> m_lastPosition;
		std::array<PressPhase, 3> phases;
		int buttons[3] = { MOUSE_INPUT_LEFT , MOUSE_INPUT_RIGHT , MOUSE_INPUT_MIDDLE };
	};

	class Touch {
	protected:
		Touch() {};
		~Touch() {};

	public:
		struct Info {
			Info() { frame = 1; time = 0; };
			Info(int x, int y, int time) {
				initPos.first = x;
				initPos.second = y;
				nowPos.first = x;
				nowPos.second = y;
				deltaPos.first = 0;
				deltaPos.second = 0;
				turnPos = nowPos;
				frame = 1;
				this->time = time;
				phase = BEGAN;
			};
			void setFlicked(bool b = false) { hasNeverFlickYet = b; };
			void setLastFlickLine(int line, FlickDirection d) {
				flickedLine = line; flickDirection = d;
			};
			std::pair<int, int> initPos;
			std::pair<int, int> nowPos;
			std::pair<int, int> deltaPos; //前フレームとの差
			std::pair<int, int> turnPos;
			int frame;
			int time;
			FlickDirection flickDirection = FlickDirection::INVALID;
			int flickedLine = 0;
			bool hasNeverFlickYet = true;
			int initLine;
			int nowLine;
			int lastLine;
			PressPhase phase;
		};

		static Touch& getInstance() { static Touch touch; return touch; };

		void update();
		std::map<int, Info>& getAllTouchInfo() { return touches; };
		const Info* getFirstTouch() {
			if (firstTouch == touches.end()) return nullptr;
			return &firstTouch->second;
		};
	private:
		Timer timer;
		std::map<int, Info> touches;
		std::map<int, std::pair<int, int>> keys; //ID, 座標
		int firstTouchId;
		decltype(touches.find(0)) firstTouch;
	};


	class DeresutePlayTouchInput : public InputDevice::Touch {
	protected:
		DeresutePlayTouchInput() {};
		virtual ~DeresutePlayTouchInput() {};

	public:
		static DeresutePlayTouchInput& getInstance2() { static DeresutePlayTouchInput touch; return touch; };

		void update();

		const TouchMap& getTouchLine() const { return touchLine; };
		const TouchMap& getHoldInitLine() const { return holdInitLine; };
		const TouchMap& getHoldLine() const { return holdLine; };
		const TouchMap& getFlickLeftLine() const { return flickLeftLine; };
		const TouchMap& getFlickRightLine() const { return flickRightLine; };
		const TouchMap& getReleaseInitLine() const { return releaseInitLine; };
		const TouchMap& getReleaseLine() const { return releaseLine; };

	private:
		TouchMap touchLine; //line, id
		TouchMap holdInitLine;
		TouchMap holdLine;
		TouchMap flickLeftLine;
		TouchMap flickRightLine;
		TouchMap releaseInitLine;
		TouchMap releaseLine;
	};
}
