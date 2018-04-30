#include "drawTriangle.h"

	int drawTriangle::triangleCount = 0;
	
	//constructors read triangles needs to use this somehow
	drawTriangle::drawTriangle(float width, float height, float positionX, float positionY, int arrSize) {
		this->positionX = positionX;
		this->positionY = positionY;
		this->width = width;
		this->height = height;
		this->size = arrSize;
		this->vertices = calcVerts();
		triangleCount++;
		for (int i = 0; i < arrSize; i++) {
			this->verts[i] = vertices->at(i);
		}	
		this->initTriangle();
	}

	//depreciated
	drawTriangle::drawTriangle() {
		this->size = 9;
		this->vertices = this->getRandVerts();
		triangleCount++;
		for (int i = 0; i < 9; i++) {
			this->verts[i] = vertices->at(i);
		}
		this->initTriangle();
	}

	//currently read is passing a local std array to the vertice pointer, local var gets deleted and the world breaks
	//for drawRectangles (as drawRec calcs its own vertices)
	drawTriangle::drawTriangle(std::array<float, 9>* vertices) {
		this->vertices = vertices;
		triangleCount++;
		for (int i = 0; i < 9; i++) {
			this->verts[i] = vertices->at(i);
		}	
		this->initTriangle();
	}

	drawTriangle::~drawTriangle() {
			glDeleteVertexArrays(1, &this->VAO);
			glDeleteBuffers(1, &this->VBO);
			//delete[] this->verts;
	}
	
	//TODO Create only one instance of this object to handle all the triangles, send all triangles in VAO at once to buffer
	void drawTriangle::initTriangle() {
		//Creates VBO Buffer object, binds arraybuffer to VBO and sends the gpu the buffer with all the triangles's vertices
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(this->verts), this->verts, GL_STATIC_DRAW); //copy vertice data into buffer array
		
		glBindVertexArray(this->VAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
	void drawTriangle::renderTriangle() {
		//for all rendering use this shader program
		//glUseProgram(shaderProgram);

		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}
	
	void drawTriangle::printVertices() {
		for (int i = 0; i < this->size; i++) {
			std::cout << "index: " << i << " vertex: " << this->verts[i] << std::endl;
		}
	}

	std::array<float, 9>* drawTriangle::calcVerts() {
		std::array<float, 9>* returnVerts = new std::array<float, 9>();
		returnVerts->fill(0.0f);
		for (int i = 0; i < 9; i++) {
			switch (i) {
			//top vertice
			case 0:
				returnVerts->at(i) = this->positionX; //x
				returnVerts->at(i + 1) = this->positionY + this->height / 2; //y
				returnVerts->at(i + 2) = 0.0f; //z
				break;
			//left corner
			case 3:
				returnVerts->at(i) = this->positionX - this->width/2; //x
				returnVerts->at(i + 1) = this->positionY - this->height / 2; //y
				returnVerts->at(i + 2) = 0.0f; //z
				break;
			//right corner
			case 6:
				returnVerts->at(i) = this->positionX + this->width/2; //x
				returnVerts->at(i + 1) = this->positionY - this->height / 2; //y
				returnVerts->at(i + 2) = 0.0f; //z
				break;
			}
		}
		return returnVerts;
	}
	
	std::array<float, 9>* drawTriangle::getRandVerts() {
		std::array<float, 9>* verts = new std::array<float, 9>();
		float triangleSize = 1.0f;
		
		for (int i = 0; i < 9; i++) {
			float newVert;
			if (i + 1 % 3 == 0) {
				newVert = 0.0f;
			}
			else {
				float random1 = ((float)rand()) / (float)RAND_MAX;
				float random2 = ((float)rand()) / (float)RAND_MAX;
				float negVert = random1 * -triangleSize;
				float posVert = random2 * triangleSize;
				newVert = negVert + posVert;
			}
			verts->at(i) = newVert;
		}
		return verts;
	}
	
	int drawTriangle::countTriangle() {
		return triangleCount;
	}