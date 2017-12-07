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
	
	int getLine(int x) { return std::max(std::min((x - offsetX) / judgeX, numLine-1), 0); }; //x座標からラインを返す
	int getCenterPosition(float line) { return offsetX + static_cast<int>(judgeX * (line + 0.5)); };//ラインから、そのラインの中央のx座標を返す
	void setNumLine(int num) { numLine = num; offsetX = (CommonSettings::WINDOW_WIDTH - (judgeX * numLine)) / 2; };
	const int& getLineWidth() const { return judgeX; };
private:
	int offsetX = 0;
	int numLine = 5;
	int judgeY = 597;
	int judgeX = 214; //(JUDGE_X * (i + 1)) がi番目の座標
	static constexpr int JUDGE_SIZE = 90;
	static constexpr int CENTER_X = CommonSettings::WINDOW_WIDTH / 2;
};