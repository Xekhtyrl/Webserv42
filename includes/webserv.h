#pragma once

#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "../srcs/HTTPProtocol/HTTPRequest.hpp"
#include "../srcs/HTTPProtocol/HTTPReponse.hpp"
#include "template.hpp"
#include <fstream>
#include <vector>
class HTTPRequest;

std::string					strTrim(std::string str, std::string set);
std::string					getTimeStamp();
std::string					requestToResponseProcess(std::string req);
std::string					fileToStr(std::string filename);
std::vector<unsigned char>	binaryFileToVector(std::string filename);
bool						isBinaryFile(std::string filename, std::string& type);
std::string					vecToStr(std::vector<unsigned char>& vec);
void						executePOST(HTTPRequest& request, std::string & response);
void						executeDELETE(HTTPRequest& request, std::string& response);
void						executeGET(HTTPRequest& request, std::string& response);
void						StrToBinaryFile(std::string filename, std::string& body, std::string boundary);
void						StrToTextFile(std::string filename, std::stringstream& s, std::string boundary);

// ces macro sont defini ici par facilité de code mais seront des valeurs recuperer du conf file
#define EXTENSION_CGI ".py"
#define GET_LOCATION "./webdata/"
#define POST_LOCATION "./webdata/"
#define MAX_CLIENT_SIZE 100000