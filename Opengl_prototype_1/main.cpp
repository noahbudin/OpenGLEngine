#include "main.h"
#include <iostream>

/**
/CONSTANTS
/TODO: Clean up constants list, abstract into objects more?
**/
float red = 0.835f;
float green = 0.7f;
float blue = 0.0f;
const int width = 800;
const int height = 600;
char* previousState = "up";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

//checks for escape key, will close window
void processInput(GLFWwindow* window, ReadWriteLevelInfo* readWrite, std::vector<drawTriangle*> triangles) {
	int escapeKey = glfwGetKey(window, GLFW_KEY_ESCAPE);
	int rKey = glfwGetKey(window, GLFW_KEY_R);
	int wKey = glfwGetKey(window, GLFW_KEY_W);
	if (escapeKey == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (wKey == GLFW_PRESS) {
		readWrite->changeFilename();
		readWrite->writeFile(triangles);
	}
	if (rKey == GLFW_PRESS) {
		triangles.clear();
		triangles = readWrite->readFile();
	}
}

//checks for space key and places single random triangle on press
bool processSpaceKey(GLFWwindow* window) {
		int spaceKey = glfwGetKey(window, GLFW_KEY_SPACE);
	
		if (spaceKey == GLFW_RELEASE) {
			previousState = "up";
		}
		if (spaceKey == GLFW_PRESS && previousState == "up") {
			std::cout << "Space Key Pressed!" << std::endl;
			previousState = "down";
			return true;
		}
		else {
			return false;
		}
}



//main implementation
int main() {
	// generate random seed for rand() to use later
	srand(static_cast <unsigned> (time(0))); 

	//initialize read/write object
	ReadWriteLevelInfo* read = new ReadWriteLevelInfo();

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
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	std::vector<drawTriangle*> triangles;//stores all my triangles

	while (!glfwWindowShouldClose(window)) { //rendering loop
		processInput(window, read, triangles); //listens for key/mouse input
		if (processSpaceKey(window)) {
			drawTriangle* tempT = new drawTriangle();
			triangles.push_back(tempT);
		}
		
		glClear(GL_COLOR_BUFFER_BIT);
		//TODO change how this works so it is more friendly to the draw triangles class
		if (!triangles.empty()) {
			for (int i = 0; i < triangles.size(); i++) {
				triangles.at(i)->renderTriangle();
			}
		}
	
		glfwSwapInterval(1); //this limits rendering to the refresh rate of the monitor
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	std::cout << "triangles in vector: " << triangles.size();

	for (int i = 0; i < triangles.size(); i++) {
		delete triangles[i];
	}

	glfwTerminate(); //safely deletes all objects and stuff with glfw

	return 0;
}
