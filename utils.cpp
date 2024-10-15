#include "webserv.h"

std::string strTrim(std::string str, std::string set) {
	int	n;
	int	start;

	if (str.empty())
		return ("");
	start = 0;
	while (set.find(str[start], 0) <= str.size())
		start++;
	n = str.size() - 1;
	while (set.find(str[n], 0) <= str.size() && n != 0)
		n--;
	return (str.substr(start, n - start + 1));
}