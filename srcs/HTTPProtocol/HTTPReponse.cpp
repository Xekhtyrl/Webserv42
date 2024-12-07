
#include "HTTPReponse.hpp"

// Default constructor
HTTPReponse::HTTPReponse() { return; }
HTTPReponse::HTTPReponse(std::string errorMsg, ServerConfig& conf) {
	int code = atoi(errorMsg.substr(0, errorMsg.find(':')).c_str());

	_statusLine = "HTTP/1.1 " + errorMsg.substr(0, errorMsg.find(':')) + "\r\n";

	_header =	headerLineFormat("Date", getTimeStamp()) + \
				headerLineFormat("Content-Type", "text/html");
	if (conf[code]){
		appendToVector(_body, fileToStr(conf.getErrorPage(code)));}
	else{
		appendToVector(_body, fileToStr("./error/404.html"));}
	_header += headerLineFormat("Content-Length", ftToString(_body.size()));
	formResponse(0);

	if (errorMsg.find(':') < errorMsg.size()){
		std::string message = errorMsg.substr(errorMsg.find(':')); // check if size tot needed;
		updateHTML(_body, message);
	}
}
HTTPReponse::HTTPReponse(std::vector<unsigned char> body, HTTPRequest& request) {
	std::string tmp;
	std::string statusStr;
	
	std::cout<<request.getStatus()<<std::endl;
	if (request.getStatus() == "200"){
		statusStr = "OK";
		_header =	headerLineFormat("Date", getTimeStamp()) + \
				headerLineFormat("Connection", "close");
		_body = body;
	}
	else if (request.getStatus() == "302"){
		statusStr = "Found";
		_header += headerLineFormat("Location", request.getHeader()["Location"]);
	}
	_statusLine = "HTTP/1.1 " + request.getStatus() + " OK\r\n";
	
	if (!body.empty() && request.getContent().find(".py") > request.getContent().size()) { //check for body or if CGI (.py)
		isBinaryFile(request.getContent(), tmp);
		_header += headerLineFormat("Content-Type", tmp);
		_header += headerLineFormat("Content-Length", ftToString(_body.size()));
	}

	formResponse(request.getContent().find(".py") < request.getContent().size());
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
void	HTTPReponse::formResponse(int CGI) {
	appendToVector(_final, _statusLine);
	appendToVector(_final, _header);
	if (!CGI)
		appendToVector(_final, "\r\n");
	if (!_body.empty())
		appendToVector(_final,_body);
}

std::string HTTPReponse::headerLineFormat(std::string val, std::string content){
	return val + ": " + content + "\r\n";
}

void HTTPReponse::updateHTML(std::vector<unsigned char> body, std::string errorMsg){
	for (int i = 0; i < 26; i++)
		body.pop_back();
	
	appendToVector(body, "\t\t<p>");
	appendToVector(body, errorMsg);
	appendToVector(body, "</p>\r\n\t</div>\r\n</body>\r\n</html>\r\n");
}