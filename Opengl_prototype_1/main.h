#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "drawTriangle.h"
#include <vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void shaderSuccess(unsigned int shader, char* shaderType);
void shaderProgramSuccess(unsigned int program, char* programType);
unsigned int* drawTriangles();