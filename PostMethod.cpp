#include "webserv.h"

void	uploadFile(std::string boundary, HTTPRequest& request, std::string& response, std::stringstream& s){
	std::string filename;
	std::string tmp;
	std::string body = request.getBody();
	
	getline(s, tmp, '\n');
	if (!boundary.empty() && tmp == boundary){
		getline(s, tmp, '\n');
		if (tmp.find("filename=") < tmp.size())
			filename = strTrim(tmp.substr(tmp.find("filename=") + 9), "\r\n\" ");
		for (int i = 0; i < 2; i++)
			getline(s, tmp, '\n');
	}
	if (filename.empty())
		throw std::runtime_error("400 Bad Request");
	filename = (POST_LOCATION + filename);

	if (isBinaryFile(request.getContent(), tmp))
		StrToBinaryFile(filename, body, boundary);
	else
		StrToTextFile(filename, s, boundary);
	response = "File uploaded successfully.\r\n";
}

void	POSTsimpleContent(std::string& response, std::string body){
	response = "Input received and stocked: " + body;
}


void	executePOST(HTTPRequest& request, std::string& response) {
	std::string body = request.getBody();
	std::stringstream s(body);
	std::string Content = request.getHeader()["Content-Type"];
	std::string boundary;

	if (Content.find("multipart/form-data") < Content.size()) {
		boundary = boundary.substr(boundary.find("boundary=") + 9);
		boundary = strTrim(boundary, "\" \n");
		uploadFile(boundary, request, response, s);
	}
	else if (Content.find("application/x-www-form-urlencoded") < Content.size()) {
		POSTsimpleContent(response, body);}
	else if (Content.find("text/plain") < Content.size()) {
		POSTsimpleContent(response, body);}
	else {
		throw std::runtime_error("400 Bad Request");}
}