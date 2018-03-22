#include "ReadLevelInfo.h"

ReadLevelInfo::ReadLevelInfo() {
	filename = "tempFileName.txt";
}

void ReadLevelInfo::changeFilename(char* newFilename) {
	delete filename; 
	filename = newFilename;
	delete newFilename; //this line may cause trouble 
	newFilename = nullptr;
}

void ReadLevelInfo::readFile() {

}

void ReadLevelInfo::writeFile() {

}