#pragma once

#include "../../includes/webserv.hpp"
#include <sstream>

template <typename T>
std::string ftToString(T value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

template <typename T>
bool	findWithIter(T& pos, T end, int size, std::string toFind) {
	int i = 0;
	for (T it = pos; it != end && i < size; it++) {
		if (*it != toFind[i++])
			return false;
	}
	return true;
}

template <typename T>
void	appendToVector(std::vector<unsigned char>& vec, T container){
	vec.insert(vec.end(), container.begin(), container.end());
}

// template <typename T>
// class Content {
// 	public:
// 		Content(T& c){
// 			_c = c;
// 		}
// 		Content(const T&oth){
// 			_c = oth._c;
// 		}
// 		Content &operator=(const T&oth){
// 			_c = oth._c;
// 			return *this;
// 		}
// 		~Content(){}
// 		T _c;
// };