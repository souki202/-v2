#include "Scene.h"
#include "Factory.h"

void Scene::update()
{
	if (loading.getHasComplete() && !isExecuteLoadComplete && !myFactory.getHaveNextScene()) {
		onLoadComplete();
		isExecuteLoadComplete = true;
	}
	else if(!loading.getHasComplete()) {
		loading.update();
		isExecuteLoadComplete = false;
	}
}

void Scene::draw()
{
	if (!isExecuteLoadComplete) loading.draw();
}
