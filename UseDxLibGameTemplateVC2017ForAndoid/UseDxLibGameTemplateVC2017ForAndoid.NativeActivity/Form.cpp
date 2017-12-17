#include "Form.h"
Form::Form()
{
	noteImageManager.loadImage();
	factory.setNewScene<SelectMusic>();
}

Form::~Form()
{
}

bool Form::update()
{
	timer.update();
	factory.update();
	factory.changeScene();

	if (factory.getScene()) {
		factory.getScene()->update();
		loading.updateLoadCount();
		factory.getScene()->draw();
	}
	factory.draw();
	return true;
}