#include "drawRectangle.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Textures\stb_image.h"

drawRectangle::drawRectangle(float width, float height, float positionX, float positionY) {
	this->width = width;
	this->height = height;
	this->position = new std::array<float, 2>;
	this->position->at(0) = positionX;
	this->position->at(1) = positionY;
	this->vertices = this->calcVerts();
	this->texture;

	//drawTriangle twice passing array size 9 of vertices based off of width, height, center calculations
	//also may be drawing corner vertices twice due to drawTriangle being called twice (optimize late)
	this->initRectangle();
	//this->genTexture();
}


drawRectangle::~drawRectangle() {
	delete this->vertices;
	delete this->position;
	this->position = nullptr;
	this->vertices = nullptr;
}

std::array<float, 18>* drawRectangle::calcVerts() {
	std::array<float, 18>* returnVerts = new std::array<float, 18>;
	returnVerts->fill(0.0f);

	for (int i = 0; i < 18; i++) {
		switch (i) {
		case 0://bottom right vertex
			returnVerts->at(i) = this->position->at(0) + this->width / 2; //x
			returnVerts->at(i + 1) = this->position->at(1) - this->height / 2; //y
			break;
		case 3://top right vertex
			returnVerts->at(i) = this->position->at(0) + this->width / 2;
			returnVerts->at(i + 1) = this->position->at(1) + this->height / 2;
			break;
		case 6://top left vertex
			returnVerts->at(i) = this->position->at(0) - this->width / 2;
			returnVerts->at(i + 1) = this->position->at(1) + this->height / 2;
			break;
			//bottom left triangle
		case 9://top left vertex
			returnVerts->at(i) = this->position->at(0) - this->width / 2; //x
			returnVerts->at(i + 1) = this->position->at(1) + this->height / 2; //y
			break;
		case 12://bottom left vertex
			returnVerts->at(i) = this->position->at(0) - this->width / 2;
			returnVerts->at(i + 1) = this->position->at(1) - this->height / 2;
			break;
		case 15: //bottom right vertex
			returnVerts->at(i) = this->position->at(0) + this->width / 2;
			returnVerts->at(i + 1) = this->position->at(1) - this->height / 2;
			break;
		}
	}
	for (int i = 0; i < returnVerts->size(); i++) {
		std::cout << i << ": " << returnVerts->at(i) << " " << std::endl;
	}
	return returnVerts;
}

void drawRectangle::initRectangle() {
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertices->size(), this->vertices, GL_STATIC_DRAW); //copy vertice data into buffer array

	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	GLenum error = glGetError();
	std::cout << "ERRORS: " << error << std::endl;
}

void drawRectangle::renderRectangle() {
	//for all rendering use this shader program
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, this->texture);
	glBindVertexArray(this->VAO);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void drawRectangle::genTexture() {
	int nrChannels;
	int tempTexInt = 10;
	unsigned char* data = stbi_load("Textures/cat.jpg", &tempTexInt, &tempTexInt, &nrChannels, 0);
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "BROKEN TEXTURE ALSO FIX THIS MESSAGE" << std::endl;
	}
	stbi_image_free(data);
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