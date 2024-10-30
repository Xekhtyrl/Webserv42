#include "../../includes/webserv.hpp"

void	executeGET(HTTPRequest& request, std::vector<unsigned char>& response, ServerConfig& conf) {
	if (isBinaryFile(request.getContent(), request.getHeader()["Content-Type"])){
		std::vector<unsigned char> vec = binaryFileToVector(request.getContent());
		response = vec;
	}
	else
		appendToVector(response, fileToStr(request.getContent()));
	if (response.size() > conf.getClientMaxBodySize()){
		response.clear();
		throw std::runtime_error(E400);}
	request.addToHeader("Content-Length", ftToString(response.size()));
}