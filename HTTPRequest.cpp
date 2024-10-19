#include "HTTPRequest.hpp"

// Default constructor
HTTPRequest::HTTPRequest() { return; }

HTTPRequest::HTTPRequest(std::string request) { 
	std::ofstream file ("./requestLog", std::ios::out);
	file<<request<<std::endl;
	file.close();
	std::string tmp = request.substr(0, request.find_first_of('\r'));
	_method = tmp.substr(0, tmp.find_first_of(32));
	if (!checkMethod(_method))
		std::runtime_error("405 Method Not Allowed");
	_content = tmp.substr(tmp.find_first_of(' ') + 1, tmp.find_last_of(' ') - tmp.find_first_of(' ') - 1);
	if (!checkLink(_content))
		std::runtime_error("404 Not Found");
	_protocolHTTP = tmp.substr(tmp.find_last_of(' ') + 1, tmp.length() - tmp.find_last_of(' ')); // needed to check?
	std::cout<<_protocolHTTP<<std::endl;
	if (_protocolHTTP.find("HTTP/1.1") > _protocolHTTP.size())
		throw std::runtime_error("400 Bad Request");
	_header = splitHeader(request);
	if (!_header["Content-Lengtgh"].empty() || !_header["Transfer-Encoding"].empty())
		_body = request.substr(request.find("\r\n\r\n") + 4, request.size() - request.find("\r\n\r\n") - 4);
	else
		_body = "";
	checkHeaders();
	return;
}

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
	std::cout<<"REQUEST DELETED"<<std::endl;
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
std::map<std::string, std::string>	HTTPRequest::getHeader() const {
	return _header;
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
	(void)link;
	return true;
}

void	HTTPRequest::checkHeaders() {
	if (_header["Host"].empty())
		throw std::runtime_error("400 Bad Request");
	if (_method == "POST"){
		if (_header["Content-Length"].empty())
			throw std::runtime_error("411 Length Required");
		if (_header["Content-Type"].empty() || (_header["Content-Length"].empty() && !_body.empty())
			|| !_header["Range"].empty() || !_header["If-Modified-Since"].empty() || !_header["If-None-Matc"].empty())
			throw std::runtime_error("400 Bad Request");
	}
	if (_method == "DELETE")
		if ((_body.empty() && (!_header["Content-Type"].empty() || !_header["Content-Length"].empty())))
			throw std::runtime_error("400 Bad Request");
	if (!_body.empty() && (_header["Content-Type"].empty() || _method == "GET"))
		throw std::runtime_error("400 Bad Request");
}

void	HTTPRequest::addToHeader(std::string val, std::string cont) {
	_header[val] = cont;
}