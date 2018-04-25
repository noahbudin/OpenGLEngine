#pragma once
#include "drawTriangle.h"
#include <array>

class drawRectangle {
	public:
		drawRectangle(float width, float height, float position);
		~drawRectangle();
		float getWidth();
		float getHeight();
		float getArea();
		float getPos();

	private:
		//something
		float height;
		float width;
		float position;
		std::array<float, 18> calcVerts(float width, float height, float position);
		std::array<float, 18> vertices;
};