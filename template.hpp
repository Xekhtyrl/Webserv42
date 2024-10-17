#pragma once

#include "webserv.h"
#include <sstream>

template <typename T>
std::string ftToString(T value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}