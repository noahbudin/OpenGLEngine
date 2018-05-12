#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <array>

//class defs
class drawTriangle {
	public:
		std::array<float, 12>* vertices;
		unsigned int VBO;
		unsigned int VAO;
		int size;
		drawTriangle(float width, float height, float positionX, float positionY, char* textureLocation);
		drawTriangle(std::array<float, 9>* vertices);
		~drawTriangle();
		void printVertices();
		void renderTriangle();

	private:
		float positionX;
		float positionY;
		float width;
		float height;
		char* textureLocation;
		unsigned int texture;
		static int triangleCount;
		void initTriangle();
		void genTexture();
		std::array<float, 12>* calcVerts();
};