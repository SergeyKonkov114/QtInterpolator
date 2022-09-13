#include "FileReader.h"
#include <fstream>

FileReader::FileReader()
{
}

FileReader::FileReader(const std::string& fp)
	: filePath(fp)
{
}

void FileReader::setFilePath(const std::string& fp) {
	filePath = fp;
}

std::vector<double> FileReader::getData() {
	std::ifstream input(filePath);
	if (!input.is_open()) {
		throw std::runtime_error("Error while reading file.");
	}
	if (input.eof()) {
		throw std::invalid_argument("Source file is empty");
	}
	std::vector<double> data_array;
	double value;
	while (!input.eof()) {
		if (input >> value) {
			data_array.push_back(value);
		}
		else {
			throw std::runtime_error("Invalid input format.");
		}
	}
	return data_array;
}