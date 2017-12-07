#pragma once
#include <memory>
#include "Scene.h"
#define factory Factory::getInstance()

class Factory {
private:
	Factory() {};
	~Factory() {};

public:
	static Factory& getInstance() { static Factory f; return f; };

	template <typename _class, typename... _Args>
	void setNewScene(_Args&&... __args);

	void changeScene() {
		if (isChange) scene = std::move(nextScene);
		isChange = false;
	};
	const std::unique_ptr<Scene>& getScene() { return scene; }

private:
	std::unique_ptr<Scene> scene;
	std::unique_ptr<Scene> nextScene;

	bool isChange = false;
};

template<typename _class, typename... _Args>
inline void Factory::setNewScene(_Args&&... __args)
{
	Scene *s = static_cast<Scene*>(new _class(std::forward<_Args>(__args)...));
	nextScene.reset(s);
	isChange = true;
}
