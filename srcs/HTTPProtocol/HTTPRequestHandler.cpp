#include "HTTPReponse.hpp"
#include "HTTPRequest.hpp"
#include <cstdio>
#include <unistd.h>
#include "../../includes/webserv.h"

//NEED TO BE DONE :|
void	executeCGI(HTTPRequest& request, std::string& response, ServerConfig& conf) {
	(void)request;
	(void)response;
}

void	executeRequest(HTTPRequest& request, std::string& response, ServerConfig& conf){
	if (request.getMethod() == "GET")
		executeGET(request, response, conf);
	else if (request.getMethod() == "POST" && request.getContent().find(EXTENSION_CGI) < request.getContent().size())
		executeCGI(request, response, conf);
	else if (request.getMethod() == "POST")
		executePOST(request, response, conf);
	else if (request.getMethod() == "DELETE")
		executeDELETE(request, response, conf);
}
// PROTECT BODY SIZE LIMIT!!!
std::string	requestToResponseProcess(std::string req, ServerConfig& conf) {
	std::string final;
	std::string repBody;

	try {
		HTTPRequest request(req, conf);
		executeRequest(request, repBody, conf); //CGI???
		HTTPReponse response(repBody, request);
		final = response.getFinal();
	}
	catch (std::exception& e) {
		HTTPReponse error((std::string)e.what(), conf);
		return (error.getFinal());
	}
	return (final);
}