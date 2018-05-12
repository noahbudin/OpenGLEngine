#include "drawRectangle.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Textures\stb_image.h"

drawRectangle::drawRectangle(float width, float height, float positionX, float positionY, char* textureLocation) {
	this->width = width;
	this->height = height;
	this->position = new std::array<float, 2>{positionX, positionY};
	this->vertices = this->calcVerts();
	this->texture;
	this->textureLocation = textureLocation;

	this->genTexture();
	this->initRectangle();
}


drawRectangle::~drawRectangle() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	delete this->vertices;
	delete this->position;
	this->position = nullptr;
	this->vertices = nullptr;
}

std::array<float, 24>* drawRectangle::calcVerts() {
	std::array<float, 24>* returnVerts = new std::array<float, 24>;
	returnVerts->fill(0.0f);

	for (int i = 0; i < 24; i++) {
		switch (i) {
		//bottom left triangle first
		case 0://top left vertex
			returnVerts->at(i) = this->position->at(0) - this->width / 2;
			returnVerts->at(i + 1) = this->position->at(1) + this->height / 2;
			returnVerts->at(i + 2) = 0.0f; //tex x
			returnVerts->at(i + 3) = 1.0f; //tex y
			break;
		case 4://bottom right vertex
			returnVerts->at(i) = this->position->at(0) + this->width / 2; //x
			returnVerts->at(i + 1) = this->position->at(1) - this->height / 2; //y
			returnVerts->at(i + 2) = 1.0f; //tex x
			returnVerts->at(i + 3) = 0.0f; //tex y
			break;
		case 8://bottom left vertex
			returnVerts->at(i) = this->position->at(0) - this->width / 2;
			returnVerts->at(i + 1) = this->position->at(1) - this->height / 2;
			returnVerts->at(i + 2) = 0.0f; //tex x
			returnVerts->at(i + 3) = 0.0f; //tex y
			break;

		//top right triangle
		case 12://top left vertex
			returnVerts->at(i) = this->position->at(0) - this->width / 2;
			returnVerts->at(i + 1) = this->position->at(1) + this->height / 2;
			returnVerts->at(i + 2) = 0.0f; //tex x
			returnVerts->at(i + 3) = 1.0f; //tex y
			break;
		case 16://top right vertex
			returnVerts->at(i) = this->position->at(0) + this->width / 2;
			returnVerts->at(i + 1) = this->position->at(1) + this->height / 2;
			returnVerts->at(i + 2) = 1.0f; //tex x
			returnVerts->at(i + 3) = 1.0f; //tex y
			break;
		case 20://bottom right vertex
			returnVerts->at(i) = this->position->at(0) + this->width / 2; //x
			returnVerts->at(i + 1) = this->position->at(1) - this->height / 2; //y
			returnVerts->at(i + 2) = 1.0f; //tex x
			returnVerts->at(i + 3) = 0.0f; //tex y
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
	//note 2 object verts and two texture verts
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (GLvoid*)0);
	//unbind array buffers and vertex attr arrays
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void drawRectangle::renderRectangle() {
	//for all rendering use this shader program
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void drawRectangle::genTexture() {
	//read textures
	int width, height, nrChannels;

	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	unsigned char* data = stbi_load(this->textureLocation, &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else {
		std::cout << "FAILED TO LOAD TEXTURE" << std::endl;
	}
	stbi_image_free(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
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