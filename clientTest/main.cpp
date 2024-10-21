#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Client.hpp"

int main(int argc, char **argv) {

	if (argc == 1) {
		std::cout << "Please enter the number of client connections, and optional port" << std::endl;
		std::cout << "./client number_of_clients [port:8080]" << std::endl;
	}
	//int n_clients = atoi(argv[1]);
	int port = 8080;
	if (argc == 3)
		port = atoi(argv[2]);

	Client A(port, "A");
    Client B(port, "B");
	// Client C(port, "C");
	// Client D(port, "D");

    A.talk(1);
	B.talk(2);
	
    return 0;
}
