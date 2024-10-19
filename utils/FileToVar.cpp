#include "webserv.h"

std::string fileToStr(std::string filename) {
	std::string fileStr;
	std::string tmp;
	std::ifstream file;
	
	file.open(filename, std::ios::in);
	if (!file)
		throw std::runtime_error("404 Not Found");
	while(getline(file, tmp)){
		tmp.append("\r\n");
		fileStr.append(tmp);
	}
	file.close();
	return fileStr;
}

std::vector<unsigned char>	binaryFileToVector(std::string filename) {
	std::ifstream file(filename, std::ios::in | std::ios::binary);
	if (!file)
		throw std::runtime_error("404 Not Found");
	std::vector<unsigned char>str((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
	file.close();
	return str;
}

std::string	vecToStr(std::vector<unsigned char>& vec) {
	std::string str;
	str.resize(vec.size());

	for (size_t i = 0; i < vec.size(); i++)
		str[i] = vec[i];
	return str;
}