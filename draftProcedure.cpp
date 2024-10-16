#include "HTTPReponse.hpp"
#include "HTTPRequest.hpp"


//ALL THIS IS JUST AN IDEA, DRAFT OF HOW IT WOULD PROCEED
//Quid de un fork seulement dans le cas de CGI et donc de la separation en 3 par method, retourne juste le prompt pour execve? et execve dans executeRequest?
void	executeGET(HTTPRequest request) {

}
void	executePOST(HTTPRequest request) {

}
void	executeDELETE(HTTPRequest request) {

}

void	executeRequest(HTTPRequest request){
	if (request.getMethod() == "GET")
		executeGET(request);
	else if (request.getMethod() == "POST")
		executePOST(request);
	else if (request.getMethod() == "DELETE")
		executeDELETE(request);
}

void	requestToResponseProcess(std::string req) {
	try{
		HTTPRequest request(req);
		executeRequest(request); //CGI???
		HTTPReponse reponse;
		request.~HTTPRequest();
		reponse.~HTTPReponse();
	}
	catch (std::exception& e) {
		HTTPReponse error((std::string)e.what());
		error.~HTTPReponse();
	}
}