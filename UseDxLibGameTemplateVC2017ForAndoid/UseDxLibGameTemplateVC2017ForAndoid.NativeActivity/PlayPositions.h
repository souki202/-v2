#pragma once
#include <algorithm>
#undef max
#undef min
#define playPositions PlayPositions::getInstance()

class PlayPositions {
private:
	PlayPositions() {};
	~PlayPositions() {};

public:
	static PlayPositions& getInstance() { static PlayPositions p; return p; };
	
	int getLine(int x) { return std::max(std::min((x - offsetX) / judgeX, numLine-1), 0); }; //x���W���烉�C����Ԃ�
	int getCenterPosition(float line) { return offsetX + static_cast<int>(judgeX * (line + 0.5)); };//���C������A���̃��C���̒�����x���W��Ԃ�
	void setNumLine(int num) { numLine = num; offsetX = (CommonSettings::WINDOW_WIDTH - (judgeX * numLine)) / 2; };
	const int& getLineWidth() const { return judgeX; };
private:
	int offsetX = 0;
	int numLine = 5;
	int judgeY = 597;
	int judgeX = 214; //(JUDGE_X * (i + 1)) ��i�Ԗڂ̍��W
	static constexpr int JUDGE_SIZE = 90;
	static constexpr int CENTER_X = CommonSettings::WINDOW_WIDTH / 2;
};