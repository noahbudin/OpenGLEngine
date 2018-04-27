// note: each triangle object is written in this way: {1, 2, 3, 4, 5, 6, 7, 8, 9}\n
#include "ReadLevelInfo.h"

ReadWriteLevelInfo::ReadWriteLevelInfo() {
	this->filename = "LevelData/tempFileName.txt";
}

std::string ReadWriteLevelInfo::validateInput() {
	bool validInput = false;
	std::string invalidChars = "!@#$%^&*()+=<>?,./;':\"[] {}\\\n";
	std::string userInput;

	while (validInput == false) {
		validInput = true;
		std::cout << "Enter a new filename: ";
		std::getline(std::cin, userInput);
		for (int i = 0; i < userInput.length(); i++) {
			if (invalidChars.find(userInput[i]) != -1) {
				std::cout << "Invalid character! Please only enter letters" << std::endl;
				validInput = false;
			}
		}
	}

	return userInput;
}

void ReadWriteLevelInfo::changeFilename() {
	std::string input = validateInput();
	//need to not change filename to cancel later on
	if (input == "cancel" || input == "c") {
		this->filename = "cancel";
		return;
	}
	std::string directory = "LevelData/";
	input = directory + input + ".txt";
	std::cout << input << std::endl;
	this->filename = input;
}

//read file reading by char? ends verts are not right...
std::vector<drawTriangle*>* ReadWriteLevelInfo::readFile(std::vector<drawTriangle*>* triangles) {
	std::cout << "Read File" << std::endl;
	std::vector<drawTriangle*>* triangleList = new std::vector<drawTriangle*>;
	std::ifstream inFile;
	std::string x;
	std::string lastFilename = this->filename;
	bool exists = false;
	
	while (!exists) {//check that file exists
		this->changeFilename();
		std::ifstream inFile(this->filename);
		if (inFile.good() || this->filename == "cancel") {
			exists = true;
		}
		else {
			std::cout << "Filename does not exist!" << std::endl;
		}
	}
	
	if (this->filename != "cancel") {
		inFile.open(this->filename);
		//if not cancel
		if (triangles->size() != 0) {
			for (int i = 0; i < triangles->size(); i++) {
				delete triangles->at(i);
				triangles->at(i) = NULL;
			}
			delete triangles;
			triangles = NULL;
		}

		//read data and construct triangle
		while (std::getline(inFile, x)) {
			std::vector<float> newTVerts;
			std::array<float, 9>* passedVerts = new std::array<float, 9>();

			//reading character codes, need to account for multiple nums and negatives ect. (sep by commas)
			for (int i = 1; i < x.size() + 1; i++) {
				if (i % 2 == 0) {
					newTVerts.push_back(x[i]);
				}
			}
			for (int i = 0; i < 9; i++) {
				passedVerts->at(i) = newTVerts.at(i);
			}

			//print verts of each triangle
			std::cout << "{";
			for (int i = 0; i < 9; i++) {
				std::cout << passedVerts->at(i);
				std::cout << ",";
			}
			std::cout << "}" << std::endl;
			//end of print verts
			drawTriangle* newT = new drawTriangle(passedVerts);
			triangleList->push_back(newT);
		}
		inFile.close();
		std::cout << "Success!" << std::endl;
	}

	else {
		delete triangleList;
		triangleList = triangles;
		this->filename = lastFilename;
		std::cout << "Read canceled..." << std::endl;
	}
	
	return triangleList;
}

void ReadWriteLevelInfo::writeFile(std::vector<drawTriangle*>* triangles, std::vector<drawRectangle*>* rectangles) {
	std::cout << "Write File" << std::endl;
	this->changeFilename();
	if (this->filename == "cancel") {
		std::cout << "Write canceled..." << std::endl;
		return;
	}
	std::ofstream ofstr;
	ofstr.open(this->filename);
	for (int i = 0; i < triangles->size(); i++) {
		ofstr << "{";
		for (int z = 0; z < 9; z++) {
			//write to file index i
			if (z < 9 - 1) {
				ofstr << triangles->at(i)->vertices->at(z) << ",";
			}
			else {
				ofstr << triangles->at(i)->vertices->at(z);
			}
		}
		ofstr << "}\n";
	}

	for (int i = 0; i < rectangles->size(); i++) {
		std::vector<drawTriangle*>* trianglesFromRec = rectangles->at(i)->getTriangles();
		for (int r = 0; r < 2; r++) {
			ofstr << "{";
			for (int z = 0; z < 9; z++) {
				//write to file index i
				if (z < 9 - 1) {
					ofstr << trianglesFromRec->at(r)->vertices->at(z) << ",";
				}
				else {
					ofstr << trianglesFromRec->at(r)->vertices->at(z);
				}
			}
			ofstr << "}\n";
		}
	}
	ofstr.close();
	std::cout << "Success!" << std::endl;
}