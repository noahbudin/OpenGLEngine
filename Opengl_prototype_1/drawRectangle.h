#pragma once
#include "drawTriangle.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <array>
#include <vector>

class drawRectangle {
	public:
		drawRectangle(float width, float height, float positionX, float positionY, char * textureLocation, int windowWidth, int windowHeight);
		~drawRectangle();
		unsigned int VBO;
		unsigned int VAO;
		unsigned int texBuffer;
		unsigned int texture;
		float getWidth();
		float getHeight();
		float getArea();
		void renderRectangle();
		std::array<float, 2>* getPos();

	private:
		int windowWidth;
		int windowHeight;
		
		int height;
		int width;
		float heightgl;
		float widthgl;
		std::array<float, 2>* position;
		std::array<float, 2>* positiongl;
		std::array<float, 24>* calcVerts();
		std::array<float, 2>* screenToOpenglXY();
		std::array<float, 24>* vertices;
		char* textureLocation;
		void genTexture();
		void initRectangle();
};