#include "drawTriangle.h"

	int drawTriangle::triangleCount = 0;
	
	/**
	/SHADERS 
	/TODO: Read shaders from a file instead of writing to a string here
	/Writing into a GLSL file would enable color changes ect...
	**/
	
	const char* drawTriangle::vertexShaderSource = 
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	
	const char* drawTriangle::fragShaderSource = 
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main(){\n"
		"FragColor = vec4(0.0f, 0.4f, 1.0f, 1.0f);\n"
		"}\0";

	//constructors
	drawTriangle::drawTriangle(std::array <float, 9> vertices, int arrSize) {
		this->shaderProgram = this->createShaderProgram();
		this->size = arrSize;
		this->vertices = vertices;
		triangleCount++;
		for (int i = 0; i < arrSize; i++) {
			this->verts[i] = vertices[i];
		}	
		this->initTriangle();
		this->countTriangle();
	}

	drawTriangle::drawTriangle() {
		this->shaderProgram = this->createShaderProgram();
		this->size = 9;
		this->vertices = this->getRandVerts();
		triangleCount++;
		for (int i = 0; i < 9; i++) {
			this->verts[i] = vertices[i];
		}
		this->initTriangle();
		this->countTriangle();
	}

	drawTriangle::~drawTriangle() {
			glDeleteVertexArrays(1, &this->VAO);
			glDeleteBuffers(1, &this->VBO);
			//delete[] this->verts;
	}
	
	unsigned int drawTriangle:: createShaderProgram() {
		//store and compile vertex shader from above vertexShaderSource
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &this->vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		
		unsigned int fragShader;
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragShader, 1, &this->fragShaderSource, NULL);
		glCompileShader(fragShader);

		//confirm the shader compilation did not burn to the ground
		this->shaderSuccess(vertexShader, "Vertex Shader");
		this->shaderSuccess(fragShader, "Fragment Shader");

		//link shaders together in a shader program and create the program
		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragShader);
		glLinkProgram(shaderProgram);
		
		//confirm successful linking
		this->shaderProgramSuccess(shaderProgram, "Vertex and Fragment Link");
		
		//delete shaders after they've been linked
		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);

		return shaderProgram;
	};

	//TODO Create only one instance of this object to handle all the triangles, send all triangles in VAO at once to buffer
	void drawTriangle::initTriangle() {
		//Creates VBO Buffer object, binds arraybuffer to VBO and sends the gpu the buffer with all the triangles's vertices
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(this->verts), this->verts, GL_STATIC_DRAW); //copy vertice data into buffer array
		
		glBindVertexArray(this->VAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
	void drawTriangle::renderTriangle() {
		//for all rendering use this shader program
		glUseProgram(shaderProgram);

		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}
	
	void drawTriangle::printVertices() {
		for (int i = 0; i < this->size; i++) {
			std::cout << "index: " << i << " vertex: " << this->verts[i] << std::endl;
		}
	}
	
	std::array<float, 9> drawTriangle::getRandVerts() {
		std::array<float, 9> verts;
		float triangleSize = 1.0f;
		
		for (int i = 0; i < 9; i++) {
			float newVert;
			if (i + 1 % 3 == 0) {
				newVert = 0.0f;
			}
			else {
				float random1 = ((float)rand()) / (float)RAND_MAX;
				float random2 = ((float)rand()) / (float)RAND_MAX;
				float negVert = random1 * -triangleSize;
				float posVert = random2 * triangleSize;
				newVert = negVert + posVert;
			}
			verts[i] = newVert;
		}
		return verts;
	}
	
	int drawTriangle::countTriangle() {
		return triangleCount;
	}

	//Both success functions give errors if there are any problems with shaders
	void drawTriangle::shaderSuccess(unsigned int shader, char* shaderType) {
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

	void drawTriangle::shaderProgramSuccess(unsigned int program, char* programType) {
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
