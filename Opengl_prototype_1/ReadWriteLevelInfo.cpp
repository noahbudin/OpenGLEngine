// note: each triangle object is written in this way: {1, 2, 3, 4, 5, 6, 7, 8, 9}\n
#include "ReadLevelInfo.h"

ReadWriteLevelInfo::ReadWriteLevelInfo() {
	filename = "tempFileName.txt";
}

void ReadWriteLevelInfo::changeFilename() {
	
	char* newFilename = "";
	std::cout << "Enter a new filename: ";
	std::cin >> newFilename;
	std::cout << std::endl;
	std::cout << newFilename;
	//filename = newFilename;
}

void ReadWriteLevelInfo::readFile() {

}

void ReadWriteLevelInfo::writeFile(std::vector<drawTriangle> triangles) {
	std::ofstream ofstr;
	ofstr.open(filename);

	for (int i = 0; i < triangles.size(); i++) {
		ofstr << "{";
		for (int z = 0; z < 9; z++) {
			//write to file index i
			if (z < 9 - 1) {
				ofstr << triangles.at(i).vertices.at(z) << ",";
			}
			else {
				ofstr << triangles.at(i).vertices.at(z);
			}
		}
		ofstr << "}\n";
	}
	ofstr.close();
}