#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <array>

//class defs
class drawTriangle {
public:
	float verts[9];
	std::array<float, 9> vertices;
	unsigned int VBO;
	unsigned int VAO;
	int size;
	drawTriangle(std::array<float, 9> vertices, int arrSize);
	void printVertices();
	int countTriangle();

private:
	static int triangleCount;
	void newTriangle();
};