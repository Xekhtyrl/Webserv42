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
# include "../includes/webserv.hpp"

int main(int argc, char **argv) {
	//get the configs from the conf file

	Config config;

	try {
		config.checkParameters(argc, argv);
		config.parseConfigFile();
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << '\n';
		exit(1);
	}

	std::vector<ServerConfig> configs;
	std::set<int> ports = config.getPorts();
	for (std::set<int>::iterator it = ports.begin(); it != ports.end(); it++) {
		std::cout<<(int)*it<<std::endl;
		configs.push_back(config.getServers()[*it]);
	}
	
	//initialize the servers vector, containing our running servers.
	std::vector<Server*> servers;
	for (std::vector<ServerConfig>::iterator it = configs.begin(); it < configs.end(); ++it) {
		servers.push_back(new Server(*it));
	}

	//initialize the server operations manager from the servers vector
	Manager serverManager(servers);

	//run it all
	serverManager.loop();
}