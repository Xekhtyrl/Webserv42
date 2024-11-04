#include "HTTPReponse.hpp"
#include "HTTPRequest.hpp"
#include <cstdio>
#include <unistd.h>
#include "../../includes/webserv.hpp"

//NEED TO BE DONE :|
void	executeCGI(HTTPRequest& request, std::vector<unsigned char>& response, ServerConfig& conf) {
	(void)request;
	(void)response;
	(void)conf;
}

void	executeRequest(HTTPRequest& request, std::vector<unsigned char>& response, ServerConfig& conf){
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
void	requestToResponseProcess(Client& client, ServerConfig& conf) {
	std::vector<unsigned char> final;
	std::vector<unsigned char> repBody;

	try {
		HTTPRequest request(client, conf);
		executeRequest(request, repBody, conf); //CGI???
		HTTPReponse response(repBody, request);
		final = response.getFinal();
	}
	catch (std::exception& e) {
		if (e.what() == (std::string)"incomplete")
			return;
		HTTPReponse error((std::string)e.what(), conf);
		client.appendWriteBuffer(error.getFinal());
	}
	client.appendWriteBuffer(final);
	client.clearReadBuffer();
}