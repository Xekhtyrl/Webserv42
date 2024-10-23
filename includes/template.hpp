#pragma once

#include "../../includes/webserv.h"
#include <sstream>

template <typename T>
std::string ftToString(T value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
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