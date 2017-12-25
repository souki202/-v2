#include "Form.h"
Form::Form()
{
	noteImageManager.loadImage();
	myFactory.setNewScene<SelectMusic>();
}

Form::~Form()
{
}

bool Form::update()
{
	timer.update();
	myFactory.update();
	myFactory.changeScene();

	if (myFactory.getScene()) {
		myFactory.getScene()->update();
		loading.updateLoadCount();
	}
	return true;
}

bool Form::draw()
{
	if (myFactory.getScene()) {
		myFactory.getScene()->draw();
	}
	myFactory.draw();
	return true;
}
