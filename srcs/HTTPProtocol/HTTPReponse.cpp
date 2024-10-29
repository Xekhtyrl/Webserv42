
#include "HTTPReponse.hpp"

// Default constructor
HTTPReponse::HTTPReponse() { return; }
HTTPReponse::HTTPReponse(std::string errorMsg, ServerConfig& conf) {
	_statusLine = "HTTP/1.1 " + errorMsg.substr(0, errorMsg.find(':')) + "\r\n";
	_header =	headerLineFormat("Date", getTimeStamp()) + \
				headerLineFormat("Content-Type", "text/html");
	appendToVector(_body, fileToStr("./error/" + errorMsg.substr(0, 3) + ".html"));
	// _body = conf.getErrorPage(atoi((errorMsg.substr(0, 3)).c_str()));	//update with Alexis part >> need precision on method
	_header += headerLineFormat("Content-Length", ftToString(_body.size()));
	formResponse();
	if (errorMsg.find(':') < errorMsg.size()){
		std::string message = errorMsg.substr(errorMsg.find(':')); // check if size tot needed;
		updateHTML(_body, message);
	}
}
HTTPReponse::HTTPReponse(std::vector<unsigned char> body, HTTPRequest& request) {
	std::string tmp;
	
	_statusLine = "HTTP/1.1 " + request.getStatus() + " OK\r\n";
	_header =	headerLineFormat("Date", getTimeStamp()) + \
				headerLineFormat("Connection", "close");
	_body = body;
	if (!body.empty()) {
		isBinaryFile(request.getContent(), tmp);
		_header += headerLineFormat("Content-Type", tmp);
		_header += headerLineFormat("Content-Length", ftToString(_body.size()));
	}
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

std::vector<unsigned char> const	HTTPReponse::getFinal() const {
	return _final;
}
void	HTTPReponse::formResponse() {
	appendToVector(_final, _statusLine);
	appendToVector(_final, _header);
	appendToVector(_final, "\r\n");
	if (!_body.empty())
		appendToVector(_final,_body);
}

std::string HTTPReponse::headerLineFormat(std::string val, std::string content){
	return val + ": " + content + "\r\n";
}

void HTTPReponse::updateHTML(std::vector<unsigned char> body, std::string errorMsg){
	std::vector<unsigned char>::iterator it = body.end();
	for (int i = 0; i < 26; i++)
		body.pop_back();
	appendToVector(body, "\t\t<p>");
	appendToVector(body, errorMsg);
	appendToVector(body, "</p>\r\n\t</div>\r\n</body>\r\n</html>\r\n");
}