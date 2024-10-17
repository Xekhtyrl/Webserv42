#include "HTTPReponse.hpp"
#include "HTTPRequest.hpp"
#include <cstdio>
#include <unistd.h>
#include "webserv.h"

// ces macro sont defini ici par facilité de code mais seront des valeurs recuperer du conf file
#define EXTENSION_CGI ".py"
#define GET_LOCATION "./webdata"
#define POST_LOCATION "./webdata"
#define MAX_CLIENT_SIZE 100000

//ALL THIS IS JUST AN IDEA, DRAFT OF HOW IT WOULD PROCEED
void	executeGET(HTTPRequest request, std::string& response) {
	std::ifstream file(GET_LOCATION + request.getContent(), std::ios::in);
	std::string tmp;

	if (!file.is_open())
		throw std::runtime_error("404 Not Found");
	while(getline(file, tmp))
		response.append(tmp);
	file.close();
	if (response.size() > MAX_CLIENT_SIZE){
		response.clear();
		throw std::runtime_error("400 Bad Request");}
}
// Pas sur du tout de cet execution de POST :| 
void	executePOST(HTTPRequest request, std::string& response) {
	std::string filename;
	std::string tmp;
	std::string body = request.getBody();
	std::stringstream s(body);
	std::string boundary = request.getHeader()["Content-type"];

	boundary = boundary.substr(boundary.find("boundary=") + 9);
	boundary = strTrim(boundary, "\" \n");
	getline(s, tmp, '\n');
	if (tmp == boundary){
		getline(s, tmp, '\n');
		if (tmp.find("filename=") < tmp.size())
			filename = strTrim(tmp.substr(tmp.find("filename=") + 9), "\r\n\" ");
		for (int i = 0; i < 2; i++)
			getline(s, tmp, '\n');
	}
	if (filename.empty())
		throw std::runtime_error("400 Bad Request");
	filename = (POST_LOCATION + filename);

	std::ofstream file(filename, std::ios::out);

	if (!file.is_open())
		throw std::runtime_error("400 Bad Request");
	while(getline(s, tmp, '\n')){
		if (tmp == boundary)
			break;
		file<<strTrim(tmp, "\r\n")<<std::endl;
	}
	file.close();
	response = "File uploaded successfully.\r\n";
}

void	executeDELETE(HTTPRequest request, std::string& response) {
	std::string file = POST_LOCATION + request.getContent();

	if (access(file.c_str(), F_OK) == -1)
		throw std::runtime_error("404 Not Found");
	remove(file.c_str());
	response = "File removed succesfully";
}

void	executeCGI(HTTPRequest request, std::string& response) {
	(void)request, response;
}

void	executeRequest(HTTPRequest request, std::string& response){
	if (request.getMethod() == "GET")
		executeGET(request, response);
	else if (request.getMethod() == "POST" && request.getContent().find(EXTENSION_CGI) < request.getContent().size())
		executeCGI(request, response);
	else if (request.getMethod() == "POST")
		executePOST(request, response);
	else if (request.getMethod() == "DELETE")
		executeDELETE(request, response);
}

std::string	requestToResponseProcess(std::string req) {
	std::string final;
	std::string repBody;

	try {
		HTTPRequest request(req);
		executeRequest(request, repBody); //CGI???
		HTTPReponse response(repBody, request);
		final = response.getFinal();
		request.~HTTPRequest();
		response.~HTTPReponse();
	}
	catch (std::exception& e) {
		HTTPReponse error((std::string)e.what());
		return (error.getFinal());
	}
	return (final);
}