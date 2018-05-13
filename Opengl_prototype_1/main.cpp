#include "main.h"
#include <iostream>
/**TODO:
*Clean up constants list, abstract into objects more?
*
*
*
*/


/**
/CONSTANTS
**/
//background colors
float clearRed = 1.0f;
float clearGreen = 1.0f;
float clearBlue = 1.0f;
//triangle colors
float red = 0.00f;
float green = 0.00f;
float blue = 0.00f;
float colors[3] = { red, green, blue };
float colorTime = 0.0f;
//window constants
int* width = new int(250);
int* height = new int(100);
//space button bool
char* previousState = "up";
char* drawMode;
double cursorX;
double cursorY;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

//checks for key presses and does appropriate things
std::vector<drawTriangle*>* processInput(GLFWwindow* window, ReadWriteLevelInfo* readWrite, std::vector<drawTriangle*>* triangles, std::vector<drawRectangle*>* rectangles) {
	int escapeKey = glfwGetKey(window, GLFW_KEY_ESCAPE);
	int rKey = glfwGetKey(window, GLFW_KEY_R);
	int wKey = glfwGetKey(window, GLFW_KEY_W);
	int cKey = glfwGetKey(window, GLFW_KEY_C);
	if (escapeKey == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (wKey == GLFW_PRESS) {
		readWrite->writeFile(triangles, rectangles);
	}
	if (rKey == GLFW_PRESS) {
		triangles = readWrite->readFile(triangles);
		std::cout << "DONE" << std::endl;
	}
	if (cKey == GLFW_PRESS) {
		clearScreen(triangles, rectangles);
	}
	return triangles;
}

//places shape on left mouse click
bool mouse_button_callback(GLFWwindow* window) {
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_RELEASE) {
		previousState = "up";
	}
	if (state == GLFW_PRESS && previousState == "up") {
		previousState = "down";
		return true;
	}
	else {
		return false;
	}
}

//converts screen cords to opengl cords
double screenToOpengl(double cord, char* axis) {
	double returnCord;
	if (axis == "x") {
		returnCord = ((cord - (*width / 2)) / (*width / 2));
	}
	else {
		returnCord = (((*height / 2) - cord) / (*height / 2));
	}
	std::cout << "returnCord: " << returnCord << std::endl;
	std::cout << "screen coord " << axis << " : " << cord << std::endl;
	return returnCord;
}

//clears screen
void clearScreen(std::vector<drawTriangle*>* triangles, std::vector<drawRectangle*>* rectangles) {
	triangles->clear();
	rectangles->clear();
}

//main
int main() {
	//initialize read/write object
	ReadWriteLevelInfo* read = new ReadWriteLevelInfo();

	//intializes glfw, sets intial window settings
	glfwInit();  
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create glfw window and make current context
	GLFWwindow* window = glfwCreateWindow(*width, *height, "First Window", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create glfw window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	//maximizes window, gets width and height, makes window current context
	glfwMaximizeWindow(window);
	glfwGetWindowSize(window, width, height);
	glfwMakeContextCurrent(window);
	
	//use GLAD to manage pointers to opengl functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, *width, *height);
	glClearColor(clearRed, clearGreen, clearBlue, 0.0f); 
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 

	//wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	Shader currShader = Shader("Shaders/triangleVert.vert", "Shaders/triangleFrag.frag");
	currShader.use();

	//initialize UI
	UI* ui = new UI(*width, *height);

	//Note:: address of drawMode == address of currentActive in UI
	//be careful when deleting
	drawMode = ui->currActive;

	//construct object list
	std::vector<drawTriangle*>* triangles = new std::vector<drawTriangle*>;//stores all my triangles
	std::vector<drawRectangle*>* rectangles = new std::vector<drawRectangle*>;//stores all my rectangles


	/**
		RENDERING LOOP	
	**/
	while (!glfwWindowShouldClose(window)) {
		currShader.use();
		triangles = processInput(window, read, triangles, rectangles); //need to fix later?

		//if mouse is clicked and draw mode hasnt been changed by UI interaction
		if (mouse_button_callback(window)){
			if (!ui->UIMouseListener(cursorX, cursorY)) {
				if (*drawMode == 't') {
					drawTriangle* tempT = new drawTriangle(0.3, 0.3, screenToOpengl(cursorX, "x"), screenToOpengl(cursorY, "y"), "Textures/container.jpg");
					triangles->push_back(tempT);
				}
				else if (*drawMode == 'r') {
					drawRectangle* tempRec = new drawRectangle(450, 300, (int)cursorX, (int)cursorY, "Textures/cat.jpg", *width, *height);
					rectangles->push_back(tempRec);
				}
			}
		}
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		//render all triangles and rectangles from lists
		if (!triangles->empty()) {
			for (int i = 0; i < triangles->size(); i++) {
				triangles->at(i)->renderTriangle();
			}
		}
	
		if (!rectangles->empty()) {
			for (int i = 0; i < rectangles->size(); i++) {
				rectangles->at(i)->renderRectangle();
			}
		}
		//render UI elements	
		ui->UIRender();

		mouse_button_callback(window);
		glfwGetCursorPos(window, &cursorX, &cursorY); 
		glfwSwapInterval(1); //this limits rendering to the refresh rate of the monitor
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	/**
		END OF RENDERING LOOP	
	**/


	//delete all objects 
	triangles->clear();
	rectangles->clear();

	delete triangles;
	delete rectangles;
	delete read;

	glfwTerminate(); //safely deletes all objects and stuff with glfw

	return 0;
}
