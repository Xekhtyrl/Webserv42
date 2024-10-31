# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <iostream>
# include "network/ConnectSocket.hpp"
# include "network/ListenSocket.hpp"
# include "network/Server.hpp"
# include "network/Operation.hpp"
# include "network/Manager.hpp"
# include "network/Client.hpp"

# define BUFFER_SIZE 1024

int main(int argc, char **argv) {
	//get the configs from the conf file
	std::vector<ServerConfig> configs; //= parse_confif_file();
	
	//initialize the servers vector, containing our running servers.
	std::vector<Server> servers;
	for (std::vector<ServerConfig>::iterator it = configs.begin(); it < configs.end(); ++it) {
		servers.push_back(Server(*it));
	}

	//initialize the server operations manager from the servers vector
	Manager serverManager = Manager(servers);

	//run it all
	server.Manager.loop();
}