#include "FileProcessor.h"


std::string FileProcessor::readFile(std::string const& fileName) {
	std::ifstream file;
	file.open(fileName);
	if (file.is_open()) {
		std::string content((std::istreambuf_iterator<char>(file)),
			(std::istreambuf_iterator<char>()));
		return content;
		file.close();
	}
	else {
		throw std::ifstream::failure("There was a problem while opening the file " + fileName);
	}
	
}