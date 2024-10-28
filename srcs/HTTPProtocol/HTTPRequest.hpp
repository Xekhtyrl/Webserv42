#ifndef HTTPREQUEST_HPP_
#define HTTPREQUEST_HPP_

#include <iostream>
#include <map>
#include "../../includes/webserv.h"
#include <fstream>
#include <sstream>
#include <string>
#include <exception>

// Class declaration
class HTTPRequest {
 public:
  HTTPRequest();
  HTTPRequest(std::string request, ServerConfig& conf);
  HTTPRequest(const HTTPRequest &other);
  HTTPRequest &operator=(const HTTPRequest &rhs);
  ~HTTPRequest();
  std::string	getMethod() const;
  std::string	getContent() const;
  std::string	getProtocolHTTP() const;
  std::string&	getBody();
  void			addToHeader(std::string, std::string);
  std::map<std::string, std::string>	getHeader() const;
  std::string	_message;

 private:
  std::map<std::string, std::string> splitHeader(std::string request);
  bool	checkMethod(std::string method, ServerConfig& conf);
  bool	checkLink(std::string& link);
  void	checkHeaders();
  std::string	_body;
  std::string	_method;
  std::string	_content;
  std::string	_protocolHTTP;
  std::map<std::string, std::string>	_header;
};

#endif // HTTPREQUEST_HPP_
