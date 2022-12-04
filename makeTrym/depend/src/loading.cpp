#include "loading.h"




std::string loadFile(const std::filesystem::path& path)
{
	std::fstream file;

	std::stringstream filestream;
	std::string line;

	file.open(path);
	if (!file.is_open()) {
		std::cout << "file could not be read, path might be wrong" << std::endl;
		file.close();
		return "";
	}
	while (std::getline(file,  line)) {
		filestream << line << "\n";
	}
	file.close();
	return filestream.str();
}
