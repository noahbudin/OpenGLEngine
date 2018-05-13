#pragma once
#include "drawTriangle.h"
#include "drawRectangle.h"

class UI {
	public:
		UI(int windowWidth, int windowHeight);
		~UI();
		void UIRender();
		bool UIMouseListener(int mouseX, int mouseY);
		drawRectangle* rectangleButton;
		drawRectangle* triangleButton;
		char* currActive;

	private:
		double rectangleButtonX;
		double rectangleButtonY;

		double rectangleButtonWidth;
		double rectangleButtonHeight;

		double triangleButtonX;
		double triangleButtonY;

		double triangleButtonWidth;
		double triangleButtonHeight;

		char* rectangleButtonInactive;
		char* rectangleButtonActive;

		char* triangleButtonInactive;
		char* triangleButtonActive;

		int windowWidth;
		int windowHeight;

		bool UIChangeDrawMode(int mouseX, int mouseY, bool inXRec, bool inYRec, bool inXTri, bool inYTri);
		double screenToOpengl(double coord, char* axis);
		void setActive(char button);
};