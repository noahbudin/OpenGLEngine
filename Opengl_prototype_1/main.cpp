#include "main.h"
#include <iostream>
/**TODO:
*Clean up constants list, abstract into objects more?
*process input reading file into triangles only not rectangles(fix with an object class that holds all shapes?)
*
*
*/


/**
/CONSTANTS
**/
//background colors
float clearRed = 1.0f;
float clearGreen = 0.0f;
float clearBlue = 1.0f;
//triangle colors
float red = 0.00f;
float green = 0.00f;
float blue = 0.00f;
float colors[3] = { red, green, blue };
float colorTime = 0.0f;
//window constants
const int width = 1280;
const int height = 720;
//space button bool
char* previousState = "up";
char* drawMode = "t";
double cursorX;
double cursorY;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

//checks for escape key, will close window
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

//switches shape to triangle
bool processOneKey(GLFWwindow* window) {
	int oneKey = glfwGetKey(window, GLFW_KEY_1);

	if (oneKey == GLFW_RELEASE) {
		previousState = "up";
	}
	if (oneKey == GLFW_PRESS && previousState == "up") {
		previousState = "down";
		return true;
	}
	else {
		return false;
	}
}

//switches shape to square
bool processTwoKey(GLFWwindow* window) {
	int twoKey = glfwGetKey(window, GLFW_KEY_2);

	if (twoKey == GLFW_RELEASE) {
		previousState = "up";
	}
	if (twoKey == GLFW_PRESS && previousState == "up") {
		previousState = "down";
		return true;
	}
	else {
		return false;
	}
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
		returnCord = ((cord - (width / 2)) / (width / 2));
	}
	else {
		returnCord = (((height / 2) - cord) / (height / 2));
	}
	std::cout << "returnCord: " << returnCord << std::endl;
	return returnCord;
}

//clears screen
void clearScreen(std::vector<drawTriangle*>* triangles, std::vector<drawRectangle*>* rectangles) {
	triangles->clear();
	rectangles->clear();
}

//main
int main() {
	// generate random seed for rand() to use later
	srand(static_cast <unsigned> (time(0))); 
	
	//initialize read/write object
	ReadWriteLevelInfo* read = new ReadWriteLevelInfo();
	//initialize color changer
	ColorChanger* cg = new ColorChanger(red, green, blue);

	//intializes glfw
	glfwInit();  
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
	glClearColor(clearRed, clearGreen, clearBlue, 0.0f); 
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 

	//wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glDisable(GL_LIGHTING);
	//glDisable(GL_TEXTURE_2D);
	//glColor4f(1, 1, 1, 1);
	//glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	
	Shader currShader = Shader("Shaders/triangleVert.vert", "Shaders/triangleFrag.frag");
	currShader.use();

	std::vector<drawTriangle*>* triangles = new std::vector<drawTriangle*>;//stores all my triangles
	std::vector<drawRectangle*>* rectangles = new std::vector<drawRectangle*>;//stores all my rectangles


	/**
		RENDERING LOOP	
	**/
	while (!glfwWindowShouldClose(window)) {
		currShader.use();
		/** change colors
		if (!triangles->empty() || !rectangles->empty()) {
			red = cg->returnRed();
			green = cg->returnGreen();
			blue = cg->returnBlue();
			cg->changeColors();
		}

		currShader.setFloat("ourColor", red, green, blue);
		**/
		triangles = processInput(window, read, triangles, rectangles); //need to fix later?

		if (mouse_button_callback(window)){
			if (drawMode == "t") {
				drawTriangle* tempT = new drawTriangle(0.2, 0.2, screenToOpengl(cursorX, "x"), screenToOpengl(cursorY, "y"), 9);
				triangles->push_back(tempT);
			}
			else if (drawMode == "r") {
				drawRectangle* tempRec = new drawRectangle(0.5, 0.5, screenToOpengl(cursorX, "x"), screenToOpengl(cursorY, "y"));
				rectangles->push_back(tempRec);
			}
		}
		
		//change draw mode
		if (processOneKey(window)) {
			drawMode = "t";
		}
		if (processTwoKey(window)) {
			drawMode = "r";
		}
		
		glClear(GL_COLOR_BUFFER_BIT);
		
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

	delete read;
	delete cg;

	glfwTerminate(); //safely deletes all objects and stuff with glfw

	return 0;
}
