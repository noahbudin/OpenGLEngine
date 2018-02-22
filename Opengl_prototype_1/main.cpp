#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	//constant
	static int width = 800;
	static int height = 600;
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
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //kinda like an event listener, this is for resizing window

	//Triangle vertices
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	
	//Creates VBO Buffer object, binds arraybuffer to VBO and sends the gpu the buffer with all the triangles's vertices
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//vertex shader 
	const char* vertexShader = "#version 330 core"
		"layout(location = 0) in vec3 aPos"
		"void main(){"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);";





	while (!glfwWindowShouldClose(window)) { //rendering loop
		processInput(window); //listens for key/mouse input
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate(); //safely deletes all objects and stuff with glfw
	return 0;
}
