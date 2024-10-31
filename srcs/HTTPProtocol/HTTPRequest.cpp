#include "HTTPRequest.hpp"

// Default constructor
HTTPRequest::HTTPRequest() { return; }

HTTPRequest::HTTPRequest(Client& client, ServerConfig& conf) { 
	std::string request(client.getReadBuffer().begin(), client.getReadBuffer().end());
	if (incompleteHeader(client.getReadBuffer()))
		throw std::runtime_error("incomplete");

	std::string tmp = request.substr(0, request.find_first_of('\r'));

	_method = tmp.substr(0, tmp.find_first_of(32));
	if (!checkMethod(_method, conf))
		throw std::runtime_error(E405);

	_content = tmp.substr(tmp.find_first_of(' ') + 1, tmp.find_last_of(' ') - tmp.find_first_of(' ') - 1);
	if (!checkLink(_content, conf))
		throw std::runtime_error(E404 ": Ressource Not found");

	_protocolHTTP = tmp.substr(tmp.find_last_of(' ') + 1, tmp.length() - tmp.find_last_of(' ')); // needed to check?
	if (_protocolHTTP.find("HTTP/1.1") > _protocolHTTP.size())
		throw std::runtime_error(E505);

	_header = splitHeader(request);
	if (incompleteBody(client.getReadBuffer()))
		throw std::runtime_error("incomplete");
	if (_header["Content-Length"].empty() == 0)
		setBody(client.getReadBuffer());
	else
		_body.push_back('\0');

	checkHeaders(conf);
	setStatus("200");
	return;
}

/* HTTPRequest::HTTPRequest(std::string request, ServerConfig& conf) {
	std::string tmp = request.substr(0, request.find_first_of('\r'));
	_method = tmp.substr(0, tmp.find_first_of(32));
	if (!checkMethod(_method, conf))
		std::runtime_error(E405);
	_content = tmp.substr(tmp.find_first_of(' ') + 1, tmp.find_last_of(' ') - tmp.find_first_of(' ') - 1);
	if (!checkLink(_content))
		std::runtime_error(E404 +": Ressource Not found");
	_protocolHTTP = tmp.substr(tmp.find_last_of(' ') + 1, tmp.length() - tmp.find_last_of(' ')); // needed to check?
	if (_protocolHTTP.find("HTTP/1.1") > _protocolHTTP.size())
		throw std::runtime_error(E400 +": Wrong or Missing HTTP Protocol");
	_header = splitHeader(request);
	if (_header["Content-Length"].empty() == 0)
		_body = request.substr(request.find("\r\n\r\n") + 4, request.size() - request.find("\r\n\r\n") - 4);
	else
		_body = "";
	checkHeaders();
	_message = "200";
	return;
} */

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
	if (!_header.empty())
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
std::vector<unsigned char>&	HTTPRequest::getBody() {
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

bool	HTTPRequest::checkMethod(std::string method, ServerConfig& conf) {
	std::string	route;

	if (_content == "/")
		route = "/";
	else if (_content.find_first_of("/", 1) < _content.size())
			route = _content.substr(1, _content.find_first_of("/", 1) - 1);
	else
		route = _content;
	if ((method == "GET" && conf[route][GET]) || (method == "DELETE" && conf[route][DELETE])
		|| (method == "POST" && conf[route][POST]))
		return true;
	return false;
}
bool	HTTPRequest::checkLink(std::string& link, ServerConfig& conf) {
	std::string path;

	changePathURL(conf);
	if (path.find(".."))
		throw std::runtime_error("403 Forbidden: Unauthorized Path");
	if (!access(path.c_str(), F_OK))
		return false;
	return true;
}

void	HTTPRequest::checkHeaders(ServerConfig& conf) {
	if (_header["Host"].empty())
		throw std::runtime_error(E400 ": Missing Host");

	if (_method == "POST"){
		if (_header["Content-Length"].empty())
			throw std::runtime_error(E411);
		if (_header["Content-Type"].empty() || (_header["Content-Length"].empty() && !_body.empty())
			|| !_header["Range"].empty() || !_header["If-Modified-Since"].empty() || !_header["If-None-Match"].empty())
			throw std::runtime_error(E400 ": Invalid POST Header");
	}

	if (_method == "DELETE")
		if ((_body.empty() && (!_header["Content-Type"].empty() || !_header["Content-Length"].empty())))
			throw std::runtime_error(E400 ": No Content Found");

	if (!_body.empty() && (_header["Content-Type"].empty() || _method == "GET"))
		throw std::runtime_error(E400 ": Body Not Allowed");
	if (!_body.empty() && _header["Content-Length"].empty())
		throw std::runtime_error(E400 ": Bad Header");

	if ((int)_body.size() > atoi(_header["Content-Length"].c_str())
		|| atoi(_header["Content-Length"].c_str()) > conf.getClientMaxBodySize()
		|| _body.size() > conf.getClientMaxBodySize())
		throw std::runtime_error(E413);
}

void	HTTPRequest::addToHeader(std::string val, std::string cont) {
	_header[val] = cont;
}

bool	HTTPRequest::incompleteHeader(std::vector<unsigned char> buffer){
	std::string str = vecToStr(buffer);
	if (str.find("\r\n\r\n") < buffer.size())
		return false;
	return true;
}
bool	HTTPRequest::incompleteBody(std::vector<unsigned char> buffer){
	std::vector<unsigned char>::iterator it = buffer.begin();
	int l = 0;

	for (it; !findWithIter(it, buffer.end(), 4, "\r\n\r\n"); it++);
	for (int i = 0; i < 4; i++)
		it++;
	for (l = 0; l < atoi(getHeader()["Content-Length"].c_str()) && it != buffer.end(); l++)
		it++;
	if (it == buffer.end() && l < atoi(getHeader()["Content-Length"].c_str()))
		return true;
	return false;
}

void	HTTPRequest::setBody(std::vector<unsigned char> buffer){
	std::vector<unsigned char>::iterator it = buffer.begin();
	int l = 0;

	for (it; !findWithIter(it, buffer.end(), 4, "\r\n\r\n"); it++);
	for (int i = 0; i < 4; i++)
		it++;
	for (it; it != buffer.end(); it++)
		_body.push_back(*it);
}

void	HTTPRequest::changePathURL(ServerConfig& conf) {
	std::string urlBeg;
	std::string urlEnd = "";
	
	if (_content.find("/", 1) < _content.size())
		urlBeg = _content.substr(0, _content.find("/", 1) - 1);
	else
		urlBeg = _content;
	if (_content.find("/", 1) < _content.size())
		urlEnd = _content.substr(_content.find("/", 1));
	urlBeg = getRedirPath(conf, _method, urlBeg, urlEnd);
	_content = urlBeg + urlEnd;
}

//tester redirection url
//tester GET avec just enouvrant un dossier ex GET /webdata
//autoindex how it work > how to GET