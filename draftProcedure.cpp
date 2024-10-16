#include "HTTPReponse.hpp"
#include "HTTPRequest.hpp"

#define EXTENSION_CGI ".py" // A DEFINIR EN FCT DE NOS CGI OU SI PLUSIEURS EXTENSION POSSIBLE, FERAIS UNE FCONCTION

//ALL THIS IS JUST AN IDEA, DRAFT OF HOW IT WOULD PROCEED
//Quid de un fork seulement dans le cas de CGI et donc de la separation en 3 par method, retourne juste le prompt pour execve? et execve dans executeRequest?
void	executeGET(HTTPRequest request, std::string& response) {

}
void	executePOST(HTTPRequest request, std::string& response) {

}
void	executeCGI(HTTPRequest request, std::string& response) {

}
void	executeDELETE(HTTPRequest request, std::string& response) {

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
	try {
		std::string repBody;
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