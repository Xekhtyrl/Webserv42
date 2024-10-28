#include "../../includes/webserv.h"

void	uploadFile(std::string boundary, HTTPRequest& request, std::string& response, std::string& body, ServerConfig& conf){
	std::string filename;
	std::string tmp;
	std::stringstream s(body);

	getline(s, tmp, '\n');
	if (!boundary.empty() && tmp.find(boundary) < tmp.size()){
		getline(s, tmp, '\n');
		if (tmp.find("filename=") < tmp.size())
			filename = strTrim(tmp.substr(tmp.find("filename=") + 9), "\r\n\" ");
		for (int i = 0; i < 2; i++)
			getline(s, tmp, '\n');
	}
	if (filename.empty())
		throw std::runtime_error("400 Bad Request");
	filename = (POST_LOCATION + filename);
	if (access(filename.c_str(), F_OK))
		request._message = "201";
	if (isBinaryFile(request.getContent(), tmp))
		StrToBinaryFile(filename, body, boundary);
	else
		StrToTextFile(filename, s, boundary);
	response = "File uploaded successfully.\r\n";
}

void	POSTsimpleContent(std::string& response, std::string body){
	response = "Input received and stocked: " + body;
}


void	executePOST(HTTPRequest& request, std::string& response, ServerConfig& conf) {
	std::string body = request.getBody();
	std::string Content = request.getHeader()["Content-Type"];
	std::string boundary;

	if (Content.find("multipart/form-data") < Content.size()) {
		boundary = Content.substr(Content.find("boundary=") + 9);
		boundary = strTrim(boundary, "\" \n");
		uploadFile(boundary, request, response, body, conf);
	}
	else if (Content.find("application/x-www-form-urlencoded") < Content.size())
		throw std::runtime_error("405 Method Not Allowed: This POST option is not implemented");
	else if (Content.find("application/JSON") < Content.size())
		throw std::runtime_error("405 Method Not Allowed: This POST option is not implemented");
	else if (Content.find("text/plain") < Content.size())
		POSTsimpleContent(response, body);
	else
		throw std::runtime_error("400 Bad Request");
}