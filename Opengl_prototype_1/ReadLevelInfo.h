#pragma once
#include <iostream>
#include <ios>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <fstream>
#include <vector>
#include <string>
#include "drawTriangle.h"

class ReadWriteLevelInfo{
	private:
		std::string filename;
		std::string validateInput();

	public:
		ReadWriteLevelInfo();
		void changeFilename();
		void writeFile(std::vector<drawTriangle*>* triangles);
		std::vector<drawTriangle*>* readFile(std::vector<drawTriangle*>* triangles);
};