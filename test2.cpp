#include "HTTPRequest.hpp"
#include "webserv.h"
#include <string>
#include <fstream>
#include <exception>

int main(){
	std::ifstream file("./test.txt", std::ios::in);
	std::string str = "";
	std::string tmp;
	while(getline(file, tmp)){
		tmp.append("\n");
		// std::cout<<"file line >>>> "<<tmp;
		try{
			str.append(tmp);}
		catch(std::exception& e){
			std::cerr<<e.what()<<std::endl;}
	}
	// std::cout<<"str === "<<str<<""<<std::endl;
	HTTPRequest request(str);
	std::cout<<"\n\nTEEEEEESSSST "<<request.getMethod()<<" "<<request.getContent()<<" "<<request.getProtocolHTTP()<<"\nBODY >>> "<<request.getBody()<<"\nEND OF DEBBUG\n"<<std::endl;
	file.close();
}