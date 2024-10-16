
#ifndef HTTPREPONSE_HPP_
#define HTTPREPONSE_HPP_

#include "HTTPRequest.hpp"
#include <iostream>

// Class declaration
class HTTPReponse {
 public:
  HTTPReponse();
  HTTPReponse(HTTPRequest);
  HTTPReponse(const HTTPReponse &other);
  HTTPReponse &operator=(const HTTPReponse &rhs);
  std::string const getFinal() const;
  ~HTTPReponse();

 private:
  void	methodGetHeader();
  void	methodPostHeader();
  void	methodDeleteHeader();
  void	formRequest() const;
  std::string	_final;
  std::string	_statusLine;
  std::string	_header;
  std::string	_body;
};

#endif // HTTPREPONSE_HPP_
