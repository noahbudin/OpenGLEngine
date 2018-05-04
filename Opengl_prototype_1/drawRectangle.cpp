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
	this->genTexture();

	this->recVertCoords = new std::array<float, 12>();
	this->recIndices = recIndices = { 0,1,3,1,2,3 };
}


drawRectangle::~drawRectangle() {
	delete this->vertices;
	delete this->position;
	delete this->recVertCoords;
	this->position = nullptr;
	this->recVertCoords = nullptr;
	this->vertices = nullptr;
	return;
}

std::array<float, 12>* drawRectangle::calcVerts() {
	std::array<float, 12>* returnVerts = new std::array<float, 12>;
	returnVerts->fill(0.0f);

	for (int i = 0; i < 9; i++) {
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
		case 9://bottom left vertex
			returnVerts->at(i) = this->position->at(0) - this->width/2;
			returnVerts->at(i + 1) = this->position->at(1) - this->height/2;
			break;
		}
	}
	return returnVerts;
}

void drawRectangle::initRectangle() {
	//Creates VBO Buffer object, binds arraybuffer to VBO and sends the gpu the buffer with all the triangles's vertices
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW); //copy vertice data into buffer array
	
	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(6 * sizeof(float)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->RecIndices), this->recIndices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void drawRectangle::renderRectangle() {
	//for all rendering use this shader program
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void drawRectangle::genTexture() {
	int nrChannels;
	int tempTexInt = 100;
	unsigned char* data = stbi_load("Textures/cat.jpg", &tempTexInt, &tempTexInt, &nrChannels, 0);
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);
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