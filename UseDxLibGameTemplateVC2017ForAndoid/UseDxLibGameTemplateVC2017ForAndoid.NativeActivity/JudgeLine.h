#pragma once
#include <memory>
#include <algorithm>
#include "Image.h"
#include "CommonSettings.h"
#undef max
#undef min
#define judgeLine JudgeLine::getInstance()

class JudgeLine {
private:
	JudgeLine() {};
	~JudgeLine() {};

public:
	static JudgeLine& getInstance() { static JudgeLine p; return p; };
	void update() {};
	void draw();

	void loadJudgeIcons(int numOfLines = 0);
	
	int getLine(int x) { return std::max(std::min((x - offsetX) / judgeX, numLine-1), 0); }; //x座標からラインを返す
	int getCenterPosition(float line) { return offsetX + static_cast<int>(judgeX * (line + 0.5)); };//ラインから、そのラインの中央のx座標を返す
	void setNumLine(int num) { numLine = num; offsetX = (CommonSettings::WINDOW_WIDTH - (judgeX * numLine)) / 2; };
	const int& getLineWidth() const { return judgeX; };
	int GET_APPEAR_Y() const { return APPEAR_Y; };
	int GET_JUDGE_Y() const { return JUDGE_Y; };

	int GET_JUDGE_SIZE() const { return JUDGE_SIZE; };
private:
	int offsetX = 0;
	int numLine = 5;
	int judgeX = 214; //(JUDGE_X * (i + 1)) がi番目の座標
	static constexpr int JUDGE_SIZE = 90;
	static constexpr int CENTER_X = CommonSettings::WINDOW_WIDTH / 2;
	static constexpr int APPEAR_Y = 120;
	static constexpr int JUDGE_Y = 597;

	std::vector<std::unique_ptr<Image>> judgeIcons;
};