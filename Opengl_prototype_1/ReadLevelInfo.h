#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <fstream>

class ReadLevelInfo{
	private:
		char* filename;
	public:
		ReadLevelInfo();
		void changeFilename(char* newFilename);
		void writeFile();
		void readFile();

};