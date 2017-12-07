#pragma once
#include "DxLib.h"

class Scene {
public:
	Scene() {};
	virtual ~Scene() {};

	virtual void update() = 0;
	virtual void draw() = 0;
};