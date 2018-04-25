#include "drawRectangle.h"

drawRectangle::drawRectangle(float width, float height, float position) {
	this->width = width;
	this->getHeight = height;
	this->position = position;
	this->vertices = this->calcVerts(this->width, this->height, this->position);
	//drawTriangle twice passing array size 9 of vertices based off of width, height, center calculations
	//also may be drawing corner vertices twice due to drawTriangle being called twice
	std::array<float, 9> topRight;
	std::array<float, 9> bottomLeft;
	for (int i = 0; i < 18; i++) {
		if (i <= 9) {
			topRight[i] = vertices[i];
		}
		else {
			bottomLeft[i] = vertices[i];
		}
	}
	drawTriangle topRightTriangle = new drawTriangle(topRight); //array size??
}


drawRectangle::~drawRectangle() {
	return;
}

std::array<float, 18> drawRectangle::calcVerts(float width, float height, float positiion) {
	//calc verts
	//lets say pos at origin(0, 0) and verts at 110   -1-10   -110   1-10
	//height and width are both 1
	//origin is at center of hypotenuse
	//draw a triangle where 3 verts are 10, 11, -11 (top right triangle)
	//draw a second triangle where 3 verts are  1-1,-1-1, -10

	std::array<float, 18> returnVerts;

	//top right
	for (int i = 0; i < 9; i++) {
		switch (i) {
		case 0:
			returnVerts[i] = width;
			returnVerts[i + 1] = width - height;
			returnVerts[i + 2] = 0.0f;
			break;
		case 3:
			returnVerts[i] = width;
			returnVerts[i + 1] = height;
			returnVerts[i + 2] = 0.0f;
			break;
		case 6:
			returnVerts[i] = -width;
			returnVerts[i + 1] = height;
			returnVerts[i + 2] = 0.0f;
			break;
		}
	}
	//bottom left
	for (int i = 0; i < 9; i++) {
		switch (i){
			case 0:
				returnVerts[i] = width;
				returnVerts[i + 1] = -height;
				returnVerts[i + 2] = 0.0f;
				break;
			case 3:
				returnVerts[i] = -width;
				returnVerts[i + 1] = -height;
				returnVerts[i + 2] = 0.0f;
				break;
			case 6:
				returnVerts[i] = -width;
				returnVerts[i + 1] = height - width;
				returnVerts[i + 2] = 0.0f;
				break;
		}
	}
	return returnVerts;
}

float drawRectangle::getWidth() {
	return this->width;
}

float drawRectangle::getHeight() {
	return this->height;
}

float drawRectangle::getPos() {
	return this->position;
}

float drawRectangle::getArea() {
	return this->height * this->width;
}