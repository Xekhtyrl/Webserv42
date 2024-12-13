#include "HTTPReponse.hpp"
#include "HTTPRequest.hpp"
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include "../../includes/webserv.hpp"

char **setEnvCGI(HTTPRequest& request) {
	char **env;
	std::string	tmp;
	int size;
	
	if (request.getMethod() == "GET")
		size = 3;
	else
		size = 4;
	env = new char*[size];
	env[size - 1] = 0;
	env[0] = strdup(tmp.append("METHOD=" + request.getMethod()).c_str());
	if (request.getMethod() != "GET") {
		tmp = "CONTENT-TYPE=" + request.getHeader()["Content-Type"]; 
		env[1] = strdup(tmp.c_str());
		tmp = "CONTENT-LENGTH=" + request.getHeader()["Content-Type"]; //???????????????????
		env[2] = strdup(tmp.c_str());
	}
	else{
		tmp = "QUERY_STRING=" + request.getQuery();
		env[1] = strdup(tmp.c_str());
	}
	return env;
}
void	executeCGI(HTTPRequest& request, std::vector<unsigned char>& response, ServerConfig& conf) {
	char **env;
	std::string retVal;
	int fd[2];
	int input[2];
	(void)conf;

	if (pipe(fd) || pipe(input)) //the fd pipe is for retrieving the content of the executed file, the input pipe is for sending the body to the CGI file
		throw std::runtime_error("serveur error: pipe"); // don't know how to process this kind of error
	if (!access(request.getContent().c_str(), X_OK))
		throw std::runtime_error(/*ERROR ACCESS DENIED*/"ERROR ACCESS DENIED");
	env = setEnvCGI(request); //needed to send the data to create the response body int the request.getCGIExt() file... still don't know if necessary
	if (fork() == 0){
		dup2(fd[1], STDOUT_FILENO); //get the ouput
		close(fd[1]);
		close(fd[0]);
		dup2(input[0], STDIN_FILENO); //send the input
		close(input[1]);
		close(input[0]);
		std::string content = request.getContent();
		std::string path = request.getCGIPath();
		char *tab[3] = {(char *)path.c_str(), (char*)content.c_str(), 0};
		execve(path.c_str(), tab, env);
	}
	close(fd[1]);
	if (request.getMethod() == "POST"){ //send the input
		close(input[0]);
		write(input[1], vecToStr(request.getBody()).c_str(), request.getBody().size());
		close(input[1]);
	}
	int r;
	char tmp[1];
	response.clear();
	while ((r = read(fd[0], tmp, 1)) > 0){ //get the ouput
		// tmp[r] = 0;
		response.push_back(tmp[0]);
	}
	close(fd[0]);
	wait(0);
	// appendToVector(response, retVal); //return the response to be send
	//see RFC CGI
	//execve with cmd to execute extension, the name of the file to execute, env?
	//send the body to the program and then get the result at the end and send it as a response
	//file has to exist to be excuted, so need to implement a program (request.getCGIExt()) for it to be testable and prooved 
}

void	executeRequest(HTTPRequest& request, std::vector<unsigned char>& response, ServerConfig& conf){
	if (request.getMethod() != "DELETE" && request.getContent().find(request.getCGIExt()) < request.getContent().size())
		executeCGI(request, response, conf);
	else if (request.getMethod() == "GET")
		executeGET(request, response, conf);
	else if (request.getMethod() == "POST")
		executePOST(request, response, conf);
	else if (request.getMethod() == "DELETE")
		executeDELETE(request, response, conf);
}
// PROTECT BODY SIZE LIMIT!!!
void	requestToResponseProcess(Client *client, ServerConfig& conf) {
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
		client->appendWriteBuffer((std::vector<unsigned char>)error.getFinal());
	}
	client->appendWriteBuffer(final);
	client->clearReadBuffer();
}