#include "webserv.h"

bool	findWithIter(std::string::iterator pos, std::string::iterator end, int size, std::string toFind) {
	int i = 0;
	for (std::string::iterator it = pos; it != end && i < size; it++) {
		if (*it != toFind[i++])
			return false;
	}
	return true;
}

void	StrToBinaryFile(std::string filename, std::string& body, std::string boundary) {
	std::string::iterator it1 = body.begin();
	std::vector<char>str;

	if (!boundary.empty())
		for (size_t i = 0; i < body.find_first_of(boundary) + boundary.size(); i++){
			it1++;
		}
	for (std::string::iterator it = it1; it != body.end(); it++) {
		if (findWithIter(it, body.end(), boundary.size(), boundary))
			break;
		if (*it != '\r')
			str.push_back(*it);
	}
	std::ofstream file(POST_LOCATION + filename, std::ios::out);
	if (!file.is_open())
		throw std::runtime_error("400 Bad Request");
	file.write(str.data(), str.size());
	file.close();
}

void	StrToTextFile(std::string filename, std::stringstream& s, std::string boundary) {
	std::string tmp;

	std::ofstream file(filename, std::ios::out);

	if (!file.is_open())
		throw std::runtime_error("400 Bad Request");
	while(getline(s, tmp, '\n')){
		if (!boundary.empty() && tmp == boundary)
			break;
		file<<strTrim(tmp, "\r\n")<<std::endl;
	}
	file.close();
}