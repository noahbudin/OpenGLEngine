#include "drawRectangle.h"

drawRectangle::drawRectangle(float width, float height, float positionX, float positionY) {
	this->width = width;
	this->height = height;
	this->position = new std::array<float, 2>;
	this->position->at(0) = positionX;
	this->position->at(1) = positionY;
	this->vertices = this->calcVerts();

	//drawTriangle twice passing array size 9 of vertices based off of width, height, center calculations
	//also may be drawing corner vertices twice due to drawTriangle being called twice (optimize late)

	std::array<float, 9>* topRight = new std::array<float, 9>();
	std::array<float, 9>* bottomLeft = new std::array<float, 9>();
	for (int i = 0; i < 18; i++) {
		if (i < 9) {
			topRight->at(i) = this->vertices->at(i);
		}
		else {
			bottomLeft->at(i - 9) = this->vertices->at(i);
		}
	}
	this->topRightTriangle = new drawTriangle(topRight);
	this->bottomLeftTriangle = new drawTriangle(bottomLeft);
	this->recTriangles = new std::vector<drawTriangle*>();
	
	recTriangles->push_back(this->topRightTriangle);
	recTriangles->push_back(this->bottomLeftTriangle);
}


drawRectangle::~drawRectangle() {
	delete this->vertices;
	delete this->topRightTriangle;
	delete this->bottomLeftTriangle;
	delete this->position;
	return;
}

std::array<float, 18>* drawRectangle::calcVerts() {
	std::array<float, 18>* returnVerts = new std::array<float, 18>;
	returnVerts->fill(0.0f);

	for (int i = 0; i < 18; i++) {
		switch (i) {
		//top right triangle
		case 0://bottom right vertex
			returnVerts->at(i) = this->position->at(0) + this->width/2; //x
			returnVerts->at(i + 1) = this->position->at(1) - this->height/2; //y
			break;
		case 3://top right vertex
			returnVerts->at(i) = this->position->at(0) + this->width/2;
			returnVerts->at(i + 1) = this->position->at(1) + this->height/2;
			break;
		case 6://top left vertex
			returnVerts->at(i) = this->position->at(0) - this->width/2;
			returnVerts->at(i + 1) = this->position->at(1) + this->height/2;
			break;
		//bottom left triangle
		case 9://top left vertex
			returnVerts->at(i) = this->position->at(0) - this->width/2; //x
			returnVerts->at(i + 1) = this->position->at(1) + this->height/2; //y
			break;
		case 12://bottom left vertex
			returnVerts->at(i) = this->position->at(0) - this->width/2;
			returnVerts->at(i + 1) = this->position->at(1) - this->height/2;
			break;
		case 15: //bottom right vertex
			returnVerts->at(i) = this->position->at(0) + this->width/2;
			returnVerts->at(i + 1) = this->position->at(1) - this->height/2;
			break;
		}
	}
	return returnVerts;
}

void drawRectangle::renderRectangle() {
	this->topRightTriangle->renderTriangle();
	this->bottomLeftTriangle->renderTriangle();
}

float drawRectangle::getWidth() {
	return this->width;
}

float drawRectangle::getHeight() {
	return this->height;
}

std::array<float, 2>* drawRectangle::getPos() {
	return this->position;
}

float drawRectangle::getArea() {
	return this->height * this->width;
}

std::vector<drawTriangle*>* drawRectangle::getTriangles() {
	return this->recTriangles;

}