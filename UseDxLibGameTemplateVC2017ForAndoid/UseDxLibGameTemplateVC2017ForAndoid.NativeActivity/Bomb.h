#pragma once
#include <array>
#include "DxLib.h"
#include "Image.h"
#include "Timer.h"
#include "JudgeLine.h"
#include "Easing.h"
#include "Random.h"
#define bombResources BombResources::getInstance()

class BombResources {
private:
	BombResources();
	~BombResources() {};

public:
	static BombResources& getInstance() { static BombResources b; return b; };

	const std::array<int, 2>& getBombImage() const { return rawImgs; };
	const int& getKiraImage() const { return kiraImg; };
private:
	std::array<int, 2> rawImgs; //[0]circle, [1]star
	int kiraImg;
};

class Bomb {
public:
	Bomb() {};
	~Bomb() {};

	void draw();
	void update();
	
	void startBomb(int line);

	void setParticleX(int x) { particleX = x; };
	void startParticle() { isStartParticle = true; particleTimer.reset(); };
	void stopParticle() { isStartParticle = false; };
private:
	struct ParticleInfo {
		int time = 0;
		Point pos;
		int alpha = 255;
		float scale = 0.75f;
	};
	Random rnd;
	Timer bombTimer;
	Timer particleTimer;
	std::array<Image, 2> bombImgs;
	std::vector<ParticleInfo> particle;
	int particleX;

	bool isStartParticle = false;
	bool isStartBomb = false;

	static constexpr int BOMB_ANIM_TIME = 350;
	static constexpr int PARTICLE_INTERVAL = 64;
	int particleElapsedTime = 0;
	static constexpr int PARTICLE_SIZE = 64;
};