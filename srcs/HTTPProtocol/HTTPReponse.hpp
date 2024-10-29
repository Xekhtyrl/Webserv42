
#ifndef HTTPREPONSE_HPP_
#define HTTPREPONSE_HPP_

#include "HTTPRequest.hpp"
#include "../../includes/webserv.hpp"
#include <iostream>

class HTTPRequest;
// Class declaration
class HTTPReponse {
 public:
  HTTPReponse();
  HTTPReponse(std::string errorMsg, ServerConfig& conf);
  HTTPReponse(std::vector<unsigned char> body, HTTPRequest& request);
  HTTPReponse(std::string body, HTTPRequest& request);
  HTTPReponse(const HTTPReponse &other);
  HTTPReponse &operator=(const HTTPReponse &rhs);
  std::vector<unsigned char> const getFinal() const;
  ~HTTPReponse();

 private:
  void	formResponse();
  std::string headerLineFormat(std::string val, std::string content);
  std::vector<unsigned char>	_final;
  std::string	_statusLine;
  std::string	_header;
  std::vector<unsigned char>	_body;
};

#endif // HTTPREPONSE_HPP_
