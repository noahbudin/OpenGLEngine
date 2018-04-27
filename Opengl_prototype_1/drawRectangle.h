#pragma once
#include "drawTriangle.h"
#include <array>
#include <vector>

class drawRectangle {
	public:
		drawRectangle(float width, float height, float positionX, float positionY);
		~drawRectangle();
		float getWidth();
		float getHeight();
		float getArea();
		std::vector<drawTriangle*>* getTriangles();
		void renderRectangle();
		std::array<float, 2>* getPos();

	private:
		//something
		float height;
		float width;
		std::array<float, 2>* position;
		drawTriangle* topRightTriangle;
		drawTriangle* bottomLeftTriangle;
		std::array<float, 18>* calcVerts();
		std::array<float, 18>* vertices;
		std::vector<drawTriangle*>* recTriangles;
};