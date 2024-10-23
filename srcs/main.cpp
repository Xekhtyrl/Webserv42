# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
#include <iostream>
# include "network/ConnectSocket.hpp"
# include "network/ListenSocket.hpp"
# include "network/Server.hpp"

int main(int argc, char **argv) {
	if (argc > 2)
		return 1;
	
	int port = 8080;
	if (argc == 2)
		port = atoi(argv[1]);

	Server *server = new Server(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY, 5, "serv");
	
	server->launch();

	delete server;
}