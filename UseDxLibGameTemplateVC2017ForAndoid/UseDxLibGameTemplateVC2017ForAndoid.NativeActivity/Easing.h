#pragma once

namespace MyEase {
	/**
	* イージング
	* @param t 現在の経過時間
	*        d 移動が終わる時間
	*        start 開始値
	*        end 終了値
	*/
	template<typename T>
	auto easeIn(int t, int d, T start, T end) -> decltype((end - start) * t, T()) {
		float tt = static_cast<float>(t) / d;
		return start + (end - start) * tt * tt;
	}

	template<typename T>
	auto easeOut(int t, int d, T start, T end) -> decltype((end - start) * (t - 2.0f), T()) {
		float tt = static_cast<float>(t) / d;
		return start - (end - start) * tt * (tt - 2.0f);
	}

	template<typename T>
	auto easeInOut(int t, int d, T start, T end) -> decltype((end - start) * (t - 2.0f), T()) {
		float tt = static_cast<float>(t) / (d / 2.0f);
		if (tt < 1) {
			return start + (end - start) / 2 * tt * tt;
		}
		else {
			tt--;
			return start - (end - start) / 2 * (tt * (tt - 2.f) - 1.f);
		}
	}
}