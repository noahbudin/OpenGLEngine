#include "main.h"
#include <iostream>

/**
/CONSTANTS
**/
float red = 0.0f;
float green = 0.75f;
float blue = 0.5f;
const int width = 800;
const int height = 600;

/**
/SHADERS 
/TODO: Read shaders from a file instead of writing to a string here
**/
const char* vertexShaderSource = 
	"#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char* fragShaderSource =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main(){\n"
	"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {

	int escapeKey = glfwGetKey(window, GLFW_KEY_ESCAPE);
	int spaceKey = glfwGetKey(window, GLFW_KEY_SPACE);

	if (escapeKey == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (spaceKey == GLFW_PRESS) {
		std::cout << "Space Key Pressed!" << std::endl;
	}
}

void shaderSuccess(unsigned int shader, char* shaderType) {
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILATION_FAILURE-->" << shaderType << std::endl;
	}
	else {
		std::cout << "SHADER_COMPILATION_SUCCEEDED-->" << shaderType << std::endl;
	}

}

void shaderProgramSuccess(unsigned int program, char* programType) {
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM_LINKING_ERROR-->" << programType << std::endl;
	}
	else {
		std::cout << "PROGRAM_LINK_SUCCESS-->" << programType << std::endl;
	}
}

int main() {
	glfwInit(); //intializes glfw 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //window hint configures glfw options, 1st param is option, second is choice
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//create glfw window and make current context
	GLFWwindow* window = glfwCreateWindow(width, height, "First Window", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create glfw window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//use GLAD to manage pointers to opengl functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, width, height);
	glClearColor(red, green, blue, 0.0f); //put colors in seperate vars later
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //kinda like an event listener, this is for resizing window

	//wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//store and compile vertex shader from above vertexShaderSource
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	unsigned int fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSource, NULL);
	glCompileShader(fragShader);

	//confirm the shader compilation did not burn to the ground
	shaderSuccess(vertexShader, "Vertex Shader");
	shaderSuccess(fragShader, "Fragment Shader");

	//link shaders together in a shader program and create the program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);
	
	//confirm successful linking
	shaderProgramSuccess(shaderProgram, "Vertex and Fragment Link");
	
	//delete shaders after they've been linked
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	float testTriangle1[] = { //left triangle
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
	};
	
	float testTriangle2[] = { //right triangle
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f   // top 
	};

	drawTriangle t = drawTriangle(testTriangle1, 9);
	drawTriangle t2 = drawTriangle(testTriangle2, 9);
	t.printVertices();
	t2.printVertices();

	drawTriangle triangles[] = { t, t2 };
		
	while (!glfwWindowShouldClose(window)) { //rendering loop
		processInput(window); //listens for key/mouse input
		glClear(GL_COLOR_BUFFER_BIT);
		//for all rendering use this shader program
		glUseProgram(shaderProgram);
		//holy sh*t this works?!?!
		for (int i = 0; i < triangles[0].countTriangle(); i++) {
			glBindVertexArray(triangles[i].VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate(); //safely deletes all objects and stuff with glfw

	return 0;
}
