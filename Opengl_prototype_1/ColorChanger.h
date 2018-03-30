#include "GLFW/glfw3.h"
#include <ios>
#include <cmath>
#include <iostream>

class ColorChanger {
public:
	ColorChanger(float red, float green, float blue);
	void changeColors();
	float returnRed();
	float returnGreen();
	float returnBlue();

private:
	float red;
	float green;
	float blue;
	int iterator;
	std::string currColor;
	float x;
};