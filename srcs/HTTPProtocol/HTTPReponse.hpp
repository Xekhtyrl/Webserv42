
#ifndef HTTPREPONSE_HPP_
#define HTTPREPONSE_HPP_

#include "HTTPRequest.hpp"
#include "../../includes/webserv.h"
#include <iostream>

class HTTPRequest;
// Class declaration
class HTTPReponse {
 public:
  HTTPReponse();
  HTTPReponse(std::string errorMsg);
  HTTPReponse(std::string body, HTTPRequest& request);
  HTTPReponse(const HTTPReponse &other);
  HTTPReponse &operator=(const HTTPReponse &rhs);
  std::string const getFinal() const;
  ~HTTPReponse();

 private:
//   void	methodGetHeader();
//   void	methodPostHeader();
//   void	methodDeleteHeader();
  void	formResponse();
  std::string headerLineFormat(std::string val, std::string content);
  std::string	_final;
  std::string	_statusLine;
  std::string	_header;
  std::string	_body;
};

#endif // HTTPREPONSE_HPP_
