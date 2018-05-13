/*
*
* TODO:
*	Clean up opengl and screen coords for each UI element, maybe have the objects hold gl values and create with screen coords only
*
*/

#include "UI.h"

UI::UI(int windowWidth, int windowHeight) {
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	this->rectangleButtonWidth = 500;
	this->rectangleButtonHeight = 300;
	this->rectangleButtonWidthgl = this->screenToOpengl(this->rectangleButtonWidth, "w");
	this->rectangleButtonHeightgl = this->screenToOpengl(this->rectangleButtonHeight, "h");
	
	this->rectangleButtonX = windowWidth - this->rectangleButtonWidth / 2;
	this->rectangleButtonY = windowHeight / 1.5;
	this->rectangleButtonXgl = this->screenToOpengl(this->rectangleButtonX, "x");
	this->rectangleButtonYgl = this->screenToOpengl(this->rectangleButtonY, "y");

	this->triangleButtonWidth = 500;
	this->triangleButtonHeight = 300;
	this->triangleButtonWidthgl = this->screenToOpengl(this->triangleButtonWidth, "w");
	this->triangleButtonHeightgl = this->screenToOpengl(this->triangleButtonHeight, "h");

	this->triangleButtonX = windowWidth - this->triangleButtonWidth/2;
	this->triangleButtonY = windowHeight / 4.5;
	this->triangleButtonXgl = this->screenToOpengl(this->triangleButtonX, "x");
	this->triangleButtonYgl = this->screenToOpengl(this->triangleButtonY, "y");

	this->rectangleButtonInactive = "Textures/rectangleInactive.jpg";
	this->rectangleButtonActive = "Textures/rectangleActive.jpg";
	this->triangleButtonInactive = "Textures/triangleInactive.jpg";
	this->triangleButtonActive = "Textures/triangleActive.jpg";
	this->currActive = new char('t');
	this->rectangleButton = new drawRectangle(this->rectangleButtonWidthgl, this->rectangleButtonHeightgl, this->rectangleButtonXgl, this->rectangleButtonYgl, this->rectangleButtonInactive);
	this->triangleButton = new drawRectangle(this->triangleButtonWidthgl, this->triangleButtonHeightgl, this->triangleButtonXgl, this->triangleButtonYgl, this->triangleButtonActive);
}

UI::~UI() {
	delete rectangleButton;
	delete triangleButton;
}

void UI::UIRender() {
	this->triangleButton->renderRectangle();
	this->rectangleButton->renderRectangle();
}

double UI::screenToOpengl(double coord, char* axis) {
	double returnCord;
	if (axis == "x") {
		returnCord = ((coord - (windowWidth / 2)) / (this->windowWidth / 2));
	}
	else if(axis == "y"){
		returnCord = (((windowHeight / 2) - coord) / (this->windowHeight / 2));
	}
	else if (axis == "w") {
		returnCord = coord/this->windowWidth;
	}
	else if(axis == "h"){
		returnCord = coord/this->windowHeight;
	}
	return returnCord;
}

bool UI::UIMouseListener(int mouseX, int mouseY) {
	bool inXRec = false;
	bool inYRec = false;
	bool inXTri = false;
	bool inYTri = false;

	//checking rectangle button x and y
	if (mouseX <= this->rectangleButtonX + this->rectangleButtonWidth / 2 && mouseX >= this->rectangleButtonX - this->rectangleButtonWidth/2) {
		std::cout << "rec x true" << std::endl;
		inXRec = true;
	}
	if (mouseY <= this->rectangleButtonY + this->rectangleButtonHeight / 2 && mouseY >= this->rectangleButtonY - this->rectangleButtonHeight / 2) {
		std::cout << "rec y true" << std::endl;
		inYRec = true;
	}
	//checking triangle button x and y
	if (mouseX <= this->triangleButtonX + this->triangleButtonWidth / 2 && mouseX >= this->triangleButtonX - this->triangleButtonWidth/2) {
		std::cout << "tri x true" << std::endl;
		inXTri = true;
	}
	if (mouseY <= this->triangleButtonY + this->triangleButtonHeight / 2 && mouseY >= this->triangleButtonY - this->triangleButtonHeight / 2) {
		std::cout << "tri y true" << std::endl;
		inYTri = true;
	}
	return this->UIChangeDrawMode(mouseX, mouseY, inXRec, inYRec, inXTri, inYTri);
}

bool UI::UIChangeDrawMode(int mouseX, int mouseY, bool inXRec, bool inYRec, bool inXTri, bool inYTri) {
	//if both in x and y
	if (inXRec && inYRec) {
		std::cout << "clicked in recbutton" << std::endl;
		this->setActive('r');
		return true;
	}
	if (inXTri && inYTri) {
		std::cout << "clicked in trianglebutton" << std::endl;
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
		this->rectangleButton = new drawRectangle(this->rectangleButtonWidthgl, this->rectangleButtonHeightgl, this->rectangleButtonXgl, this->rectangleButtonYgl, this->rectangleButtonActive);
		this->triangleButton = new drawRectangle(this->triangleButtonWidthgl, this->triangleButtonHeightgl, this->triangleButtonXgl, this->triangleButtonYgl, this->triangleButtonInactive);
	}
	else {
		*this->currActive = 't';
		this->rectangleButton = new drawRectangle(this->rectangleButtonWidthgl, this->rectangleButtonHeightgl, this->rectangleButtonXgl, this->rectangleButtonYgl, this->rectangleButtonInactive);
		this->triangleButton = new drawRectangle(this->triangleButtonWidthgl, this->triangleButtonHeightgl, this->triangleButtonXgl, this->triangleButtonYgl, this->triangleButtonActive);
	}
}