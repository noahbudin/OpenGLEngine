/**TODO 
* Make an object class as parent to triangles and rectangles, make circles eventually
*
*
**/

#include "drawTriangle.h"
#include "Libraries/stb_image.h"

//create triangle based on width, height, position, ect.
drawTriangle::drawTriangle(float width, float height, float positionX, float positionY, char* textureLocation) {
	this->positionX = positionX;
	this->positionY = positionY;
	this->width = width;
	this->height = height;
	this->vertices = calcVerts();
	this->textureLocation = textureLocation;
	this->texture;

	this->genTexture();
	this->initTriangle();
}

drawTriangle::drawTriangle(std::array<float, 9>* vertices) {
}

drawTriangle::~drawTriangle() {
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		delete[] this->vertices;
		this->vertices = nullptr;
}

void drawTriangle::initTriangle() {
	//Creates VBO Buffer object, binds arraybuffer to VBO and sends the gpu the buffer with all the triangles's vertices
	glGenVertexArrays(1, &this->VAO);

	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertices->size(), this->vertices, GL_STATIC_DRAW); //copy vertice data into buffer array

	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void drawTriangle::renderTriangle() {
	//for all rendering use this shader program
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void drawTriangle::printVertices() {
	for (int i = 0; i < this->vertices->size(); i++) {
		std::cout << "index: " << i << " vertex: " << this->vertices->at(i) << std::endl;
	}
}

std::array<float, 12>* drawTriangle::calcVerts() {
	std::array<float, 12>* returnVerts = new std::array<float, 12>();
	returnVerts->fill(0.0f);
	for (int i = 0; i < 12; i++) {
		switch (i) {
		//top vertice
		case 0:
			returnVerts->at(i) = this->positionX; //x
			returnVerts->at(i + 1) = this->positionY + this->height / 2; //y
			returnVerts->at(i + 2) = 0.5f; //texture x
			returnVerts->at(i + 3) = 1.0f; //texture y
			break;
		//left vertice
		case 4:
			returnVerts->at(i) = this->positionX - this->width/2; //x
			returnVerts->at(i + 1) = this->positionY - this->height / 2; //y
			returnVerts->at(i + 2) = 0.0f; //texture x
			returnVerts->at(i + 3) = 0.0f; //texture y
			break;
		//right corner
		case 8:
			returnVerts->at(i) = this->positionX + this->width/2; //x
			returnVerts->at(i + 1) = this->positionY - this->height / 2; //y
			returnVerts->at(i + 2) = 1.0f; //texture x
			returnVerts->at(i + 3) = 0.0f; //texture y
			break;
		}
	}
	return returnVerts;
}

void drawTriangle::genTexture() {
	//read textures
	int width, height, nrChannels;

	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(this->textureLocation, &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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