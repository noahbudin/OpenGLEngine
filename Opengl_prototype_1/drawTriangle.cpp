#include "drawTriangle.h"

	int drawTriangle::triangleCount = 0;

	drawTriangle::drawTriangle(float vertices[], int arrSize) {
		std::cout << "Triangle created!" << std::endl;
		this->size = arrSize;
		triangleCount++;
		for (int i = 0; i < arrSize; i++) {
			this->verts[i] = vertices[i];
		}	
		this->newTriangle();
		this->countTriangle();
	}

	void drawTriangle::newTriangle() {
		std::cout << "in new triangle method!";

		//Creates VBO Buffer object, binds arraybuffer to VBO and sends the gpu the buffer with all the triangles's vertices
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);

		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(this->verts), this->verts, GL_STATIC_DRAW); //copy vertice data into buffer array
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void drawTriangle::printVertices() {
		for (int i = 0; i < this->size; i++) {
			std::cout << "index: " << i << " vertex: " << this->verts[i] << std::endl;
		}
	}

	int drawTriangle::countTriangle() {
		return triangleCount;
	}
