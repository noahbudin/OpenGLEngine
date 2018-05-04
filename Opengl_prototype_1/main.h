#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "drawTriangle.h"
#include "drawRectangle.h"
#include "ReadLevelInfo.h"
#include "ColorChanger.h"
#include "Shaders/Shader.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <array>
#include <cmath>
#include "Include/glm/glm.hpp"
#include "Include/glm/gtc/matrix_transform.hpp"
#include "Include/glm/gtc/type_ptr.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
std::vector<drawTriangle*>* processInput(GLFWwindow* window, ReadWriteLevelInfo* readWrite, std::vector<drawTriangle>* triangles);
bool processOneKey(GLFWwindow* window);
bool processTwoKey(GLFWwindow* window);
void shaderSuccess(unsigned int shader, char* shaderType);
void shaderProgramSuccess(unsigned int program, char* programType);
drawTriangle newTriangle();
float* getRandVerts();
bool mouse_button_callback(GLFWwindow* window);
double screenToOpengl(double returnCord);
double screenToOpengl(double cord, char* axis);
void clearScreen(std::vector<drawTriangle*>* triangles, std::vector<drawRectangle*>* rectangles);
void testTextures(int width, int height);