#include "../webserv.h"

void	executeDELETE(HTTPRequest& request, std::string& response) {
	std::string file = POST_LOCATION + request.getContent();

	if (access(file.c_str(), F_OK) == -1)
		throw std::runtime_error("404 Not Found");
	remove(file.c_str());
	response = "File removed succesfully: " + request.getContent();
}