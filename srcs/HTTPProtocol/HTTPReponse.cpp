
#include "HTTPReponse.hpp"

// Default constructor
HTTPReponse::HTTPReponse() { return; }
HTTPReponse::HTTPReponse(std::string errorMsg) {
	_statusLine = "HTTP/1.1 " + errorMsg + "\r\n";
	_header =	headerLineFormat("Date", getTimeStamp()) + \
				headerLineFormat("Content-Type", "text/html");
	_body = fileToStr("./error/" + errorMsg.substr(0, 3) + ".html");
	_header += headerLineFormat("Content-Length", ftToString(_body.length()));
	formResponse();
}
HTTPReponse::HTTPReponse(std::string body, HTTPRequest& request) {
	_statusLine = "HTTP/1.1 " + ftToString(200) + "\r\n";
	std::string tmp;
	isBinaryFile(request.getContent(), tmp);
	// std::cout<<tmp<<std::endl;
	_header =	headerLineFormat("Date", getTimeStamp()) + \
				headerLineFormat("Content-Type", tmp);
				headerLineFormat("Connection", "close");
	_body = body;
	_header += headerLineFormat("Content-Length", ftToString(_body.length()));
	(void)request;
	formResponse();
}
// Copy constructor
HTTPReponse::HTTPReponse(const HTTPReponse &other) {
  *this = other;
  return;
}

// Copy assignment overload
HTTPReponse &HTTPReponse::operator=(const HTTPReponse &rhs) {
  (void)rhs;
  return *this;
}

// Default destructor
HTTPReponse::~HTTPReponse() { return; }

std::string const	HTTPReponse::getFinal() const {
	return _final;
}
void	HTTPReponse::formResponse() {
	_final = _statusLine + _header + "\r\n";
	if (!_body.empty())
		_final += _body;
}

std::string HTTPReponse::headerLineFormat(std::string val, std::string content){
	return val + ": " + content + "\r\n";
}