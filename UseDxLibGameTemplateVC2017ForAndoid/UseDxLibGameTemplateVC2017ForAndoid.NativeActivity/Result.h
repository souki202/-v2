#pragma once
#include "Factory.h"
#include "Scene.h"
#include "SelectMusic.h"

class Result : public Scene {
public:
	Result() { factory.setNewScene<SelectMusic>(); };
	~Result() {};

	void update() {};
	void draw() {};
private:


};