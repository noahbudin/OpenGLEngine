#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <fstream>
#include <vector>
#include "drawTriangle.h"

class ReadWriteLevelInfo{
	private:
		char* filename;

	public:
		ReadWriteLevelInfo();
		void changeFilename();
		void writeFile(std::vector<drawTriangle> triangles);
		void readFile();

};