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
	int deltaTime = nowTime - judgeTime;

	
	//��芸�����^�b�`�����Ĕ�����N�����Ă�����̂Ƃ���B
	result.grade = calcGrade(deltaTime);
	result.id = -1;

	//�����͌�����POOR�ƁA���p�n�_�̂ݍl����B
	switch (timing) {
	case JudgeTiming::TOUCH:
		//�������Ȃ�v�Z���Ȃ�
		if (deltaTime <= -judgeRange.back()) return JudgeResult();
		result.id = searchUnuseId(touchInput.getTouchLine(), line);
		if (result.id == -1) {
			if (result.grade != JudgeGrade::POOR) result.grade = JudgeGrade::INVALID;
		}
		break;
	case JudgeTiming::RELEASE://�g�p�ς݂��l�����Ȃ�
	{
		//�ǂ����ŗ�����Ă��邱�Ƃ𒲂ׂ�
		result.id = touchId;
		bool isThere = false;
		for (auto& eachLine : touchInput.getReleaseLine()) { //���ꂼ��̃��C��(�����)
			for (auto& x : eachLine.second) { //���ꂼ���id
				if (x == touchId) { //������
					//���[���[���[���[��[!! ����������[!!!
					if (eachLine.first != line) {
						result.grade = JudgeGrade::POOR;
					}
					else {//�����Ă�c
						result.grade = calcGrade(deltaTime, true);
					}
					isThere = true;
					break;
				}
			}
			if (isThere) break;
		}
		//�����ĂȂ��Ȃ猩��������
		if (!isThere) {
			if (result.grade != JudgeGrade::POOR) result.grade = JudgeGrade::INVALID;
		}
	}
		break;
	case JudgeTiming::RELEASE_INIT://�g�p�ς݂��l�����Ȃ�
	{
		result.id = touchId;
		if (touchId != -1) { //��������LN�����Ă�?
			bool isThere = false;
			auto it = touchInput.getReleaseInitLine().find(line); //�����������̃��C���ɔ��肪���邩���ׂ�
			if (it != touchInput.getReleaseInitLine().end()) { //����Ȃ�id�����Ă���
				for (auto& x : it->second) { //���ꂼ���id���o
					isThere |= (x == touchId);
				}
			}
			//�����ĂȂ��Ȃ猩��������
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
		//�������Ȃ�v�Z���Ȃ�
		if (deltaTime <= -judgeRange.back()) return JudgeResult();
		result.id = searchUnuseId(touchInput.getFlickLeftLine(), line);
		if (result.id == -1) {
			if (result.grade != JudgeGrade::POOR) result.grade = JudgeGrade::INVALID;
		}
		break;
	case JudgeTiming::FLICK_R:
		result.grade = calcFlickGrade(deltaTime);
		//�������Ȃ�v�Z���Ȃ�
		if (deltaTime <= -judgeRange.back()) return JudgeResult();
		result.id = searchUnuseId(touchInput.getFlickRightLine(), line);
		if (result.id == -1) {
			if (result.grade != JudgeGrade::POOR) result.grade = JudgeGrade::INVALID;
		}
		break;
	case JudgeTiming::THROUGH://�g�p�ς݂��l�����Ȃ�
	{
		result.id = touchId;
		bool isThere = false;
		auto it = touchInput.getHoldLine().find(line); //�����������̃��C���ɔ��肪���邩���ׂ�
		if (it != touchInput.getHoldLine().end()) { //����Ȃ�id�����Ă���
			for (auto& x : it->second) { //���ꂼ���id���o
				isThere |= (x == touchId);
			}
		}
		//�Y�����C���������ĂȂ��Ȃ猩��������
		if (!isThere) {
			if (result.grade != JudgeGrade::POOR) result.grade = JudgeGrade::INVALID;
		}
		else { //�����Ă�Ȃ�ʂ�߂���܂Ŕ��肵�Ȃ�
			if (deltaTime < -judgeRange[static_cast<int>(JudgeGrade::PERFECT)]) {
				result.grade = JudgeGrade::INVALID;
			}
		}
	}
	{ //�m�[�g�ʉߑO�ɗ����Ă���POOR
		for (auto& eachLine : touchInput.getReleaseLine()) { //���ꂼ��̃��C��(�����)
			for (auto& x : eachLine.second) { //���ꂼ���id
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

	//���肪�ʃm�[�c�ɉe���łȂ��悤�ǉ�
	judgedId.push_back(result.id);

	view.setGrade(result.grade);

	return result;
}

JudgeGrade Judge::calcGrade(int deltaTime, bool isInLn)
{
	//BAD�܂Ŕ���
	int absDeltaTime = std::abs(deltaTime);
	for (int i = 0; i <= static_cast<int>(JudgeGrade::BAD); i++) {
		if (absDeltaTime <= judgeRange[i]) return static_cast<JudgeGrade>(i);
	}

	//������POOR
	if (deltaTime >= judgeRange[static_cast<int>(JudgeGrade::POOR)]) {
		return JudgeGrade::POOR;
	}

	//INVALID��
	if (isInLn && deltaTime < 0) return JudgeGrade::POOR;
	return JudgeGrade::INVALID;
}

JudgeGrade Judge::calcFlickGrade(int deltaTime)
{
	//BAD�܂Ŕ���
	int absDeltaTime = std::abs(deltaTime);
	JudgeGrade grade = JudgeGrade::INVALID;

	for (int i = static_cast<int>(JudgeGrade::BAD); i >= 0; i--) {
		if (absDeltaTime <= flickJudgeRange[i]) grade = static_cast<JudgeGrade>(i);
	}
	//������
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