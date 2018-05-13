/*
*
* TODO:
*	Clean up opengl and screen coords for each UI element, maybe have the objects hold gl values and create with screen coords only
*	Rectangle coordinates not lining up the way they should (thats why in cursor position checking adding by 1/4 height and width) need to figure out why later
*/

#include "UI.h"

UI::UI(int windowWidth, int windowHeight) {
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	this->rectangleButtonWidth = 500;
	this->rectangleButtonHeight = 300;
	
	this->rectangleButtonX = windowWidth - this->rectangleButtonWidth / 2;
	this->rectangleButtonY = windowHeight / 1.5;

	this->triangleButtonWidth = 500;
	this->triangleButtonHeight = 300;

	this->triangleButtonX = windowWidth - this->triangleButtonWidth/2;
	this->triangleButtonY = windowHeight / 4.5;

	this->clearButtonWidth = 500;
	this->clearButtonHeight = 300;

	this->clearButtonX = windowWidth - this->clearButtonWidth/2;
	this->clearButtonY = windowHeight/2 - this->clearButtonHeight/6;

	this->rectangleButtonInactive = "Textures/rectangleInactive.jpg";
	this->rectangleButtonActive = "Textures/rectangleActive.jpg";
	this->triangleButtonInactive = "Textures/triangleInactive.jpg";
	this->triangleButtonActive = "Textures/triangleActive.jpg";
	this->clearButtonTex = "Textures/clear.jpg";
	this->currActive = new char('t');
	this->rectangleButton = new drawRectangle(this->rectangleButtonWidth, this->rectangleButtonHeight, this->rectangleButtonX, this->rectangleButtonY, this->rectangleButtonInactive, this->windowWidth, this->windowHeight);
	this->triangleButton = new drawRectangle(this->triangleButtonWidth, this->triangleButtonHeight, this->triangleButtonX, this->triangleButtonY, this->triangleButtonActive, this->windowWidth, this->windowHeight);
	this->clearButton = new drawRectangle(this->clearButtonWidth, this->clearButtonHeight, this->clearButtonX, this->clearButtonY, this->clearButtonTex, this->windowWidth, this->windowHeight);
}

UI::~UI() {
	delete this->rectangleButton;
	delete this->triangleButton;
	delete this->clearButton;
}

void UI::UIRender() {
	this->triangleButton->renderRectangle();
	this->rectangleButton->renderRectangle();
	this->clearButton->renderRectangle();
}

bool UI::UICheckClear(int mouseX, int mouseY) {
	bool inXClear = false;
	bool inYClear = false;

	if (mouseX <= this->clearButtonX + this->clearButtonWidth / 4 && mouseX >= this->clearButtonX - this->clearButtonWidth/4) {
		inXClear = true;
	}
	if (mouseY <= this->clearButtonY + this->clearButtonHeight / 4 && mouseY >= this->clearButtonY - this->clearButtonHeight / 4) {
		inYClear = true;
	}
	if (inXClear && inYClear) {
		return true;
	}
	return false;
}

bool UI::UIMouseListener(int mouseX, int mouseY) {
	bool inXRec = false;
	bool inYRec = false;
	bool inXTri = false;
	bool inYTri = false;

	//checking rectangle button x and y
	if (mouseX <= (this->rectangleButtonX + (this->rectangleButtonWidth/4))  && mouseX >= (this->rectangleButtonX - (this->rectangleButtonWidth/4))) {
		inXRec = true;
	}
	if (mouseY <= this->rectangleButtonY + this->rectangleButtonHeight / 4 && mouseY >= this->rectangleButtonY - this->rectangleButtonHeight / 4) {
		inYRec = true;
	}
	//checking triangle button x and y
	if (mouseX <= this->triangleButtonX + this->triangleButtonWidth / 4 && mouseX >= this->triangleButtonX - this->triangleButtonWidth/4) {
		inXTri = true;
	}
	if (mouseY <= this->triangleButtonY + this->triangleButtonHeight / 4 && mouseY >= this->triangleButtonY - this->triangleButtonHeight / 4) {
		inYTri = true;
	}
	return this->UIChangeDrawMode(mouseX, mouseY, inXRec, inYRec, inXTri, inYTri);
}

bool UI::UIChangeDrawMode(int mouseX, int mouseY, bool inXRec, bool inYRec, bool inXTri, bool inYTri) {
	//if both in x and y
	if (inXRec && inYRec) {
		this->setActive('r');
		return true;
	}
	if (inXTri && inYTri) {
		this->setActive('t');
		return true;
	}
	return false;
}

void UI::setActive(char button) {
	delete this->rectangleButton;
	delete this->triangleButton;

	if (button == 'r') {
		*this->currActive = 'r';
		this->rectangleButton = new drawRectangle(this->rectangleButtonWidth, this->rectangleButtonHeight, this->rectangleButtonX, this->rectangleButtonY, this->rectangleButtonActive, this->windowWidth, this->windowHeight);
		this->triangleButton = new drawRectangle(this->triangleButtonWidth, this->triangleButtonHeight, this->triangleButtonX, this->triangleButtonY, this->triangleButtonInactive, this->windowWidth, this->windowHeight);
	}
	else {
		*this->currActive = 't';
		this->rectangleButton = new drawRectangle(this->rectangleButtonWidth, this->rectangleButtonHeight, this->rectangleButtonX, this->rectangleButtonY, this->rectangleButtonInactive, this->windowWidth, this->windowHeight);
		this->triangleButton = new drawRectangle(this->triangleButtonWidth, this->triangleButtonHeight, this->triangleButtonX, this->triangleButtonY, this->triangleButtonActive, this->windowWidth, this->windowHeight);
	}
}