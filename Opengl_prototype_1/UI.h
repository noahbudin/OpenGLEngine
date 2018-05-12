#pragma once
#include "drawTriangle.h"
#include "drawRectangle.h"

class UI {
	public:
		UI(int windowWidth, int windowHeight);
		~UI();
		void renderUI();
		bool UIMouseListen(int mouseX, int mouseY, bool clickBool);
		drawRectangle* rectangleButton;
		drawRectangle* triangleButton;

	private:
		double rectangleButtonX;
		double rectangleButtonY;
		double rectangleButtonWidth;
		double rectangleButtonHeight;
		double rectangleButtonWidthgl;
		double rectangleButtonHeightgl;
		double triangleButtonX;
		double triangleButtonY;
		double triangleButtonWidth;
		double triangleButtonHeight;
		double triangleButtonWidthgl;
		double triangleButtonHeightgl;
		char* rectangleButtonInactive;
		char* rectangleButtonActive;
		char* triangleButtonInactive;
		char* triangleButtonActive;
		char* currActive;
		int windowWidth;
		int windowHeight;
		double screenToOpengl(double coord, char* axis);
		bool checkMousePos(int mouseX, int mouseY);
		void setAcive();
};