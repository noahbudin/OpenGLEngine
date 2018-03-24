#include "drawTriangle.h"

	int drawTriangle::triangleCount = 0;

	//constructors
	drawTriangle::drawTriangle(std::array <float, 9> vertices, int arrSize, unsigned int shaderProgram) {
		this->shaderProgram = shaderProgram;
		this->size = arrSize;
		this->vertices = vertices;
		triangleCount++;
		for (int i = 0; i < arrSize; i++) {
			this->verts[i] = vertices[i];
		}	
		this->initTriangle();
		this->countTriangle();
	}

	drawTriangle::drawTriangle(unsigned int shaderProgram) {
		this->shaderProgram = shaderProgram;
		this->size = 9;
		this->vertices = this->getRandVerts();
		triangleCount++;
		for (int i = 0; i < 9; i++) {
			this->verts[i] = vertices[i];
		}
		this->initTriangle();
		this->countTriangle();
	}

	//TODO Destructor, not a super big deal now though
	//copy constructor?


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
		glUseProgram(shaderProgram);

		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}
	
	void drawTriangle::printVertices() {
		for (int i = 0; i < this->size; i++) {
			std::cout << "index: " << i << " vertex: " << this->verts[i] << std::endl;
		}
	}
	
	std::array<float, 9> drawTriangle::getRandVerts() {
		std::array<float, 9> verts;
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
			verts[i] = newVert;
		}
		return verts;
	}
	
	int drawTriangle::countTriangle() {
		return triangleCount;
	}
