#include "ColorChanger.h"

ColorChanger::ColorChanger(float red, float green, float blue) {
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->iterator = 0;
	this->currColor = "RED";
	this->x = 0.1f;
}

void ColorChanger::changeColors() {
	if (this->currColor == "RED") {
		if (this->iterator < 2) {
			float rounded = std::abs((cos(x)));
			rounded = floorf(rounded * 100) / 100;
			this->red = rounded;
			this->x += 0.01f;
			if (this->red == 0.0f || this->red == 1.0f) {
				this->iterator++;
			}
		}
		else {
			this->currColor = "GREEN";
			this->iterator = 0;
			this->x = 0;
		}
	}

	else if (this->currColor == "GREEN") {
		if(this->iterator < 2) {
			float rounded = std::abs((cos(x)));
			rounded = floorf(rounded * 100) / 100;
			this->green = rounded;
			x += 0.01f;
			if (this->green == 0.0f || this->green == 1.0f) {
				this->iterator++;
			}
		}
		else {
			this->currColor = "BLUE";
			this->iterator = 0;
			this->x = 0;
		}
	}
	else if (this->currColor == "BLUE") {
		if (this->iterator < 2) {
			float rounded = std::abs((cos(x)));
			rounded = floorf(rounded * 100) / 100;
			this->blue = rounded;
			x += 0.01f;
			if (this->blue == 0.0f || this->blue == 1.0f) {
				this->iterator++;
			}
		}
		else {
			this->currColor = "RED";
			this->iterator = 0;
			this->x = 0;
		}
	}
}
float ColorChanger::returnRed() {
	return this->red;
}
float ColorChanger::returnGreen() {
	return this->green;
}
float ColorChanger::returnBlue() {
	return this->blue;
}
