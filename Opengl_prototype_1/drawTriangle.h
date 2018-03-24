#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <array>

//class defs
class drawTriangle {
public:
	std::array<float, 9> vertices;
	unsigned int VBO;
	unsigned int VAO;
	int size;
	drawTriangle(std::array<float, 9> vertices, int arrSize, unsigned int shaderProgram);
	drawTriangle(unsigned int shaderProgram);
	void printVertices();
	int countTriangle();
	void renderTriangle();

private:
	float verts[9];
	unsigned int shaderProgram;
	static int triangleCount;
	void initTriangle();
	std::array<float, 9> getRandVerts();
};