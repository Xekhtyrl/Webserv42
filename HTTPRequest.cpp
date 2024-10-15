#include "HTTPRequest.hpp"
#include "webserv.h"
#include <unistd.h>

// Default constructor
HTTPRequest::HTTPRequest() { return; }
HTTPRequest::HTTPRequest(std::string const request) { 
	std::string tmp = request.substr(0, request.find_first_of('\n'));
	_method = tmp.substr(0, tmp.find_first_of(' '));
	// std::cout<<!checkMethod(_method)<<std::endl;
	if (!checkMethod(_method))
		return; // put adequate error here?
	_content = tmp.substr(tmp.find_first_of(' ') + 1, tmp.find_last_of(' ') - tmp.find_first_of(' ') - 1);
	// std::cout<<!checkLink(_content)<<std::endl;
	if (!checkLink(_content))
		return; // put adequate error here?
	_protocolHTTP = tmp.substr(tmp.find_last_of(' ') + 1, tmp.length() - tmp.find_last_of(' ')); // needed to check?
	_header = splitHeader(request);
	if (!_header["Content-Lengtgh"].empty() || !_header["Transfer-Encoding"].empty())
		_body = request.substr(request.find("\r\n\r\n") + 4, request.size() - request.find("\r\n\r\n") - 4);
	else
		_body = "";
	return; }

// Copy constructor
HTTPRequest::HTTPRequest(const HTTPRequest &other) {
  *this = other;
  return;
}

// Copy assignment overload
HTTPRequest &HTTPRequest::operator=(const HTTPRequest &rhs) {
  (void)rhs;
  return *this;
}

// Default destructor
HTTPRequest::~HTTPRequest() { 
	_header.clear();
	return; }

std::string	HTTPRequest::getMethod() const {
	return _method;
}
std::string	HTTPRequest::getContent() const {
	return _content;
}
std::string	HTTPRequest::getProtocolHTTP() const {
	return _protocolHTTP;
}
std::string	HTTPRequest::getBody() const {
	return _body;
}

std::map<std::string, std::string> HTTPRequest::splitHeader(std::string request) {
	std::string tmp;
	std::stringstream l(request);
	std::map<std::string, std::string> tab;
	getline(l, tmp, '\n');
	while (getline(l, tmp, '\n'))
	{
		if (tmp.empty() || tmp == "\r")
			break;
		if (tmp.find(':') <= tmp.size())
			tab[tmp.substr(0, tmp.find_first_of(':'))] = strTrim((std::string)tmp.substr(tmp.find_first_of(':') + 1, tmp.length() - tmp.find_first_of(':') - 1), "\r\t\n\v ");
	}
	return tab;
}

bool	HTTPRequest::checkMethod(std::string method) {
	if (method == "GET" || method == "DELETE" || method == "POST")
		return true;
	return false;
}
bool	HTTPRequest::checkLink(std::string& link) {
	// std::string path = ".";
	// path.append(link);
	// if (!access(path.c_str(), F_OK))
	// 	return false;
	// link = path;
	return true;
}