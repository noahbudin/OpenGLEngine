#include "ReadLevelInfo.h"

ReadLevelInfo::ReadLevelInfo() {
	filename = "tempFileName.txt";
}

void ReadLevelInfo::changeFilename() {
	
	char* newFilename = "";
	std::cout << "Enter a new filename: ";
	std::cin >> newFilename;
	
	filename = newFilename;
}

void ReadLevelInfo::readFile() {

}

void ReadLevelInfo::writeFile(float* indiceArray) {
	std::ofstream ofstr;
	ofstr.open(filename);
	std::cout << sizeof(indiceArray)<< std::endl;
	for (int i = 0; indiceArray[i] != -1.0f; i++) {
		//write to file index i
		ofstr << indiceArray[i] << ",";
	}
	ofstr.close();
}