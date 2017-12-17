#include "Judge.h"

void Judge::setJudgeDifficulty(int difficulty)
{
	switch (difficulty)
	{
	case 0:
		judgeRange[static_cast<int>(JudgeGrade::PERFECT)] = 50;
		judgeRange[static_cast<int>(JudgeGrade::GREAT)] = 100;
		judgeRange[static_cast<int>(JudgeGrade::GOOD)] = 225;
		judgeRange[static_cast<int>(JudgeGrade::BAD)] = 450;
		judgeRange[static_cast<int>(JudgeGrade::POOR)] = 451;
		flickJudgeRange[static_cast<int>(JudgeGrade::PERFECT)] = 100;
		flickJudgeRange[static_cast<int>(JudgeGrade::GREAT)] = 150; //FAST only
		flickJudgeRange[static_cast<int>(JudgeGrade::GOOD)] = 275; //FAST only
		flickJudgeRange[static_cast<int>(JudgeGrade::BAD)] = 450; //FAST only
		flickJudgeRange[static_cast<int>(JudgeGrade::POOR)] = 451;
		break;
	case 1:
		judgeRange[static_cast<int>(JudgeGrade::PERFECT)] = 33;
		judgeRange[static_cast<int>(JudgeGrade::GREAT)] = 67;
		judgeRange[static_cast<int>(JudgeGrade::GOOD)] = 167;
		judgeRange[static_cast<int>(JudgeGrade::BAD)] = 330;
		judgeRange[static_cast<int>(JudgeGrade::POOR)] = 331;
		flickJudgeRange[static_cast<int>(JudgeGrade::PERFECT)] = 66;
		flickJudgeRange[static_cast<int>(JudgeGrade::GREAT)] = 100; //FAST only
		flickJudgeRange[static_cast<int>(JudgeGrade::GOOD)] = 200; //FAST only
		flickJudgeRange[static_cast<int>(JudgeGrade::BAD)] = 330; //FAST only
		flickJudgeRange[static_cast<int>(JudgeGrade::POOR)] = 331;
		break;
	default:
		break;
	}
}

JudgeResult Judge::judge(const JudgeTiming& timing, int nowTime, int judgeTime, int line, int touchId)
{
	JudgeResult result;
	result.grade = JudgeGrade::INVALID;
	result.id = 0;
	int deltaTime = nowTime - judgeTime;

	if (playSettings.getIsAuto()) {
		if (deltaTime >= 0) {
			result.grade = JudgeGrade::PERFECT;
			cnt[static_cast<int>(result.grade)]++;
			if (result.grade <= JudgeGrade::GREAT) PlaySoundMem(tapSe, DX_PLAYTYPE_BACK);
			view.setGrade(result.grade);
		}
		return result;
	}

	
	//取り敢えずタッチ等して判定を起こせているものとする。
	result.grade = calcGrade(deltaTime);
	result.id = -1;

	//ここは見逃しPOORと、中継地点のみ考える。
	switch (timing) {
	case JudgeTiming::TOUCH:
		//早すぎなら計算しない
		if (deltaTime <= -judgeRange.back()) return JudgeResult();
		result.id = searchUnuseId(touchInput.getTouchLine(), line);
		if (result.id == -1) {
			if (result.grade != JudgeGrade::POOR) result.grade = JudgeGrade::INVALID;
		}
		break;
	case JudgeTiming::RELEASE://使用済みを考慮しない
	{
		//どこかで離されていることを調べる
		result.id = touchId;
		bool isThere = false;
		for (auto& eachLine : touchInput.getReleaseLine()) { //それぞれのライン(あれば)
			for (auto& x : eachLine.second) { //それぞれのid
				if (x == touchId) { //離した
					//ちーがーうーだーろー!! ちがうだろー!!!
					if (eachLine.first != line) {
						result.grade = JudgeGrade::POOR;
					}
					else {//あってる…
						result.grade = calcGrade(deltaTime, true);
					}
					isThere = true;
					break;
				}
			}
			if (isThere) break;
		}
		//離してないなら見逃し判定
		if (!isThere) {
			if (result.grade != JudgeGrade::POOR) result.grade = JudgeGrade::INVALID;
		}
	}
		break;
	case JudgeTiming::RELEASE_INIT://使用済みを考慮しない
	{
		result.id = touchId;
		if (touchId != -1) { //そもそもLN押してる?
			bool isThere = false;
			auto it = touchInput.getReleaseInitLine().find(line); //そもそもそのラインに判定があるか調べる
			if (it != touchInput.getReleaseInitLine().end()) { //あるならidを見ていく
				for (auto& x : it->second) { //それぞれのid抽出
					isThere |= (x == touchId);
				}
			}
			//離してないなら見逃し判定
			if (!isThere) {
				if (result.grade != JudgeGrade::POOR) result.grade = JudgeGrade::INVALID;
			}
			else {
				result.grade = calcGrade(deltaTime, true);
			}
		}
	}
		result.id = searchUnuseId(touchInput.getReleaseInitLine(), line);
		break;
	case JudgeTiming::FLICK_L:
		result.grade = calcFlickGrade(deltaTime);
		//早すぎなら計算しない
		if (deltaTime <= -judgeRange.back()) return JudgeResult();
		result.id = searchUnuseId(touchInput.getFlickLeftLine(), line);
		if (result.id == -1) {
			if (result.grade != JudgeGrade::POOR) result.grade = JudgeGrade::INVALID;
		}
		break;
	case JudgeTiming::FLICK_R:
		result.grade = calcFlickGrade(deltaTime);
		//早すぎなら計算しない
		if (deltaTime <= -judgeRange.back()) return JudgeResult();
		result.id = searchUnuseId(touchInput.getFlickRightLine(), line);
		if (result.id == -1) {
			if (result.grade != JudgeGrade::POOR) result.grade = JudgeGrade::INVALID;
		}
		break;
	case JudgeTiming::THROUGH://使用済みを考慮しない
	{
		result.id = touchId;
		bool isThere = false;
		auto it = touchInput.getHoldLine().find(line); //そもそもそのラインに判定があるか調べる
		if (it != touchInput.getHoldLine().end()) { //あるならidを見ていく
			for (auto& x : it->second) { //それぞれのid抽出
				isThere |= (x == touchId);
			}
		}
		//該当ラインを押してないなら見逃し判定
		if (!isThere) {
			if (result.grade != JudgeGrade::POOR) result.grade = JudgeGrade::INVALID;
		}
		else { //押してるなら通り過ぎるまで判定しない
			if (deltaTime < -judgeRange[static_cast<int>(JudgeGrade::PERFECT)]) {
				result.grade = JudgeGrade::INVALID;
			}
		}
	}
	{ //ノート通過前に離してたらPOOR
		for (auto& eachLine : touchInput.getReleaseLine()) { //それぞれのライン(あれば)
			for (auto& x : eachLine.second) { //それぞれのid
				if (x == touchId) result.grade = JudgeGrade::POOR;
			}
		}
	}
	break;
	case JudgeTiming::INVALID:
		result.grade = JudgeGrade::INVALID;
		result.id = -1;
		break;
	}
	if (result.grade <= JudgeGrade::GREAT) PlaySoundMem(tapSe, DX_PLAYTYPE_BACK);

	//判定が別ノーツに影響でないよう追加
	judgedId.push_back(result.id);

	view.setGrade(result.grade);
	if (result.grade != JudgeGrade::INVALID) {
		cnt[static_cast<int>(result.grade)]++;
	}
	return result;
}

JudgeGrade Judge::calcGrade(int deltaTime, bool isInLn)
{
	//BADまで判定
	int absDeltaTime = std::abs(deltaTime);
	for (int i = 0; i <= static_cast<int>(JudgeGrade::BAD); i++) {
		if (absDeltaTime <= judgeRange[i]) return static_cast<JudgeGrade>(i);
	}

	//見逃しPOOR
	if (deltaTime >= judgeRange[static_cast<int>(JudgeGrade::POOR)]) {
		return JudgeGrade::POOR;
	}

	//INVALID時
	if (isInLn && deltaTime < 0) return JudgeGrade::POOR;
	return JudgeGrade::INVALID;
}

JudgeGrade Judge::calcFlickGrade(int deltaTime)
{
	//BADまで判定
	int absDeltaTime = std::abs(deltaTime);
	JudgeGrade grade = JudgeGrade::INVALID;

	for (int i = static_cast<int>(JudgeGrade::BAD); i >= 0; i--) {
		if (absDeltaTime <= flickJudgeRange[i]) grade = static_cast<JudgeGrade>(i);
	}
	//見逃し
	if (grade >= JudgeGrade::GOOD && deltaTime > 0) {
		grade = JudgeGrade::POOR;
	}

	return grade;
}

int Judge::searchUnuseId(const InputDevice::TouchMap & touches, int line)
{
	if (touches.empty()) return -1;

	auto it = touches.find(line);
	for (auto& x : it->second) {
		if (!std::count(judgedId.begin(), judgedId.end(), x)) {
			return x;
		}
	}

	return -1;
}