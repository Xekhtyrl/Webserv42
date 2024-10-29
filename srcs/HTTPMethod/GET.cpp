#include "../../includes/webserv.hpp"

void	executeGET(HTTPRequest& request, std::string& response, ServerConfig& conf) {
	if (isBinaryFile(request.getContent(), request.getHeader()["Content-Type"])){
		std::vector<unsigned char> vec = binaryFileToVector(GET_LOCATION + request.getContent());
		response = vecToStr(vec);
	}
	else
		response = fileToStr(GET_LOCATION + request.getContent());
	if (response.size() > MAX_CLIENT_SIZE){
		response.clear();
		throw std::runtime_error("400 Bad Request");}
	request.addToHeader("Content-Length", ftToString(response.size()));
}