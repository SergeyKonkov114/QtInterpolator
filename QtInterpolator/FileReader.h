#pragma once

#include <string>
#include <vector>

class FileReader {
public:
	FileReader();
	FileReader(const std::string& fp);

	void setFilePath(const std::string& fp);
	std::vector<double> getData();

private:
	std::string filePath;
};
