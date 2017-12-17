#pragma once
#include "DxLib.h"
#include "NowLoadingWindow.h"

class Scene {
public:
	Scene() {};
	virtual ~Scene() {};

	virtual void update();
	virtual void draw();

	void updateLoadCount() { loading.updateLoadCount(); };
	virtual void onLoadComplete() {};
private:
	bool isExecuteLoadComplete = false;
};