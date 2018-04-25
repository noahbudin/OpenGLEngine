#include "ColorChanger.h"
static const float PI = 3.1415927f;
static const float change = PI/100; //speed of color change
static const float lowerTolerance = 0.00001;
static const float higherTolerance = 0.9999;

ColorChanger::ColorChanger(float red, float green, float blue) {
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->iterator = 0;
	this->currColor = "RED";
	this->current = 0.0f;
	this->delta = 0.0f;
	this->prev = -1.0f;
	this->x = PI; //color change amount (put into cos)
}

void ColorChanger::changeColors() {
	if (this->currColor == "RED") {
		this->current = cos(this->x);
		this->delta = this->current - this->prev;
		this->red += delta / 2;
		this->prev = this->current;
		this->x += change;
		if (this->red > higherTolerance) {
			this->iterator++;
		}

		if (this->red < lowerTolerance && this->iterator > 0) {
			this->currColor = "GREEN";
			this->red = 0.0f;
			this->iterator = 0;
			this->x = PI;
		}
	}

	else if (this->currColor == "GREEN") {
		this->current = cos(this->x);
		this->delta = this->current - this->prev;
		this->green += delta / 2;
		this->prev = this->current;
		this->x += change;
		if (this->green > higherTolerance) {
			this->iterator++;
		}
		if (this->green < lowerTolerance && this->iterator > 0) {
			this->currColor = "BLUE";
			this->green = 0.0f;
			this->iterator = 0;
			this->x = PI;
		}
	}

	else if (this->currColor == "BLUE") {
		this->current = cos(this->x);
		this->delta = this->current - this->prev;
		this->blue += delta / 2;
		this->prev = this->current;
		this->x += change;

		if (this->blue > higherTolerance) {
			this->iterator++;
		}
		if (this->blue < lowerTolerance && this->iterator > 0) {
			this->currColor = "RED";
			this->blue = 0.0f;
			this->iterator = 0;
			this->x = PI;
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
