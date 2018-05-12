#include "UI.h"

UI::UI(int windowWidth, int windowHeight) {
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	this->rectangleButtonWidth = 500;
	this->rectangleButtonHeight = 300;
	this->rectangleButtonWidthgl = this->screenToOpengl(this->rectangleButtonWidth, "w");
	this->rectangleButtonHeightgl = this->screenToOpengl(this->rectangleButtonHeight, "h");
	
	this->rectangleButtonX = this->screenToOpengl(windowWidth - this->rectangleButtonWidth/2, "x");
	this->rectangleButtonY = this->screenToOpengl(windowHeight / 1.5, "y");

	this->triangleButtonWidth = 500;
	this->triangleButtonHeight = 300;
	this->triangleButtonWidthgl = this->screenToOpengl(this->triangleButtonWidth, "w");
	this->triangleButtonHeightgl = this->screenToOpengl(this->triangleButtonHeight, "h");
	
	this->triangleButtonX = this->screenToOpengl(windowWidth - this->triangleButtonWidth/2, "x");
	this->triangleButtonY = this->screenToOpengl(windowHeight / 4.5, "y");

	this->rectangleButtonInactive = "Textures/rectangleInactive.jpg";
	this->rectangleButtonActive = "Textures/rectangleActive.jpg";
	this->triangleButtonInactive = "Textures/triangleInactive.jpg";
	this->triangleButtonActive = "Textures/triangleActive.jpg";
	this->currActive = "t";
	this->rectangleButton = new drawRectangle(this->rectangleButtonWidthgl, this->rectangleButtonHeightgl, this->rectangleButtonX, this->rectangleButtonY, this->rectangleButtonInactive);
	this->triangleButton = new drawRectangle(this->triangleButtonWidthgl, this->triangleButtonHeightgl, this->triangleButtonX, this->triangleButtonY, this->triangleButtonActive);
}

UI::~UI() {
	delete rectangleButton;
	delete triangleButton;
}

void UI::renderUI() {
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