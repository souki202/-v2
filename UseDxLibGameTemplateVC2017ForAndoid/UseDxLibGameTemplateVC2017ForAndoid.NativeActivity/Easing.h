#pragma once

namespace MyEase {
	/**
	* イージング
	* @param t 現在の経過時間
	*        d t=0から開始して,移動が終わる時間
	*        start 開始値
	*        end 終了値
	*        isInRange tを0<=t<=dに収めるかどうか
	*/
	template<typename T>
	auto easeIn(int t, int d, T start, T end, bool isInRange = false) -> decltype((end - start) * t, T()) {
		float tt = static_cast<float>(t) / d;
		if (isInRange) tt = std::max(std::min(tt, 1.f), 0.f);
		return start + (end - start) * tt * tt;
	}

	template<typename T>
	auto easeOut(int t, int d, T start, T end, bool isInRange = false) -> decltype((end - start) * (t - 2.0f), T()) {
		float tt = static_cast<float>(t) / d;
		if (isInRange) tt = std::max(std::min(tt, 1.f), 0.f);
		return start - (end - start) * tt * (tt - 2.0f);
	}

	template<typename T>
	auto easeInOut(int t, int d, T start, T end, bool isInRange = false) -> decltype((end - start) * (t - 2.0f), T()) {
		float tt = static_cast<float>(t) / (d / 2.f);
		if (isInRange) tt = std::max(std::min(tt, 2.f), 0.f);
		if (tt < 1) {
			return start + (end - start) / 2 * tt * tt;
		}
		else {
			tt--;
			return start - (end - start) / 2 * (tt * (tt - 2.f) - 1.f);
		}
	}
}