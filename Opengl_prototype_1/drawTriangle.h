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
		unsigned int shader;
		static const char* vertexShaderSource;
		static const char* fragShaderSource;
		int size;
		drawTriangle(float width, float height, float positionX, float positionY, int arrSize);
		drawTriangle();
		drawTriangle(std::array<float, 9> vertices);
		~drawTriangle();
		void printVertices();
		int countTriangle();
		void renderTriangle();

	private:
		float verts[9];
		float positionX;
		float positionY;
		float width;
		float height;
		unsigned int shaderProgram;
		static int triangleCount;
		void initTriangle();
		unsigned int createShaderProgram();
		std::array<float, 9> getRandVerts();
		void shaderSuccess(unsigned int shader, char* shaderType);
		void shaderProgramSuccess(unsigned int program, char* programType);
		std::array<float, 9> calcVerts();
};