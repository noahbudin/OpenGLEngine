#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "drawTriangle.h"
#include "ReadLevelInfo.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <array>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, ReadWriteLevelInfo* readWrite, std::vector<drawTriangle> triangles);
bool processSpaceKey(GLFWwindow* window);
void shaderSuccess(unsigned int shader, char* shaderType);
void shaderProgramSuccess(unsigned int program, char* programType);
drawTriangle newTriangle();
float* getRandVerts();