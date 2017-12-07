#pragma once
#include <random>

class Random {
public:
	Random();
	~Random();
	int generate(int min, int max);
private:
	static std::random_device rnd;
	static std::mt19937 mt;

	int offset;
};