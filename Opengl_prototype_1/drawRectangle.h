#pragma once
#include "drawTriangle.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <array>
#include <vector>

class drawRectangle {
	public:
		drawRectangle(float width, float height, float positionX, float positionY);
		~drawRectangle();
		unsigned int VBO;
		unsigned int VAO;
		unsigned int texture;
		float getWidth();
		float getHeight();
		float getArea();
		std::array<float, 12>* recVertCoords;
		std::array<unsigned int, 6> recIndices;
		void renderRectangle();
		std::array<float, 2>* getPos();

	private:
		//something
		float height;
		float width;
		std::array<float, 2>* position;
		std::array<float, 12>* calcVerts();
		std::array<float, 12>* vertices;
		void genTexture();
		void initRectangle();
};