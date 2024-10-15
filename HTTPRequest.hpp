#ifndef HTTPREQUEST_HPP_
#define HTTPREQUEST_HPP_

#include <iostream>

// Class declaration
class HTTPRequest {
 public:
  HTTPRequest();
  HTTPRequest(const HTTPRequest &other);
  HTTPRequest &operator=(const HTTPRequest &rhs);
  ~HTTPRequest();

 private:
  std::string	_header;
  std::string	_body;
};

#endif // HTTPREQUEST_HPP_
