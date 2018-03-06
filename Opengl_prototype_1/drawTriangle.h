#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//class defs
class drawTriangle {
public:
	float verts[9];
	unsigned int VBO;
	unsigned int VAO;
	int size;
	drawTriangle(float vertices[], int arrSize);
	void printVertices();
	int countTriangle();

private:
	static int triangleCount;
	void newTriangle();
};