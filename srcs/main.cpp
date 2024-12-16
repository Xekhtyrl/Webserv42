# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <iostream>
# include <csignal>
# include "network/ConnectSocket.hpp"
# include "network/ListenSocket.hpp"
# include "network/Server.hpp"
# include "network/Manager.hpp"
# include "network/Client.hpp"
# include "../includes/webserv.hpp"



//initialize the servers vector, containing our running servers. Globally so that we can exit them gracefully with signal handling
std::deque<Server*> servers;

void serverClear(int signum) {
	(void)signum;
	for (std::deque<Server*>::iterator it = servers.begin(); it < servers.end(); ++it) {
		delete *it;
	}
	servers.clear();
	exit(1);
}


int main(int argc, char **argv) {

	// Register signal handler for SIGINT
    std::signal(SIGINT, serverClear);


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
		configs.push_back(config.getServers()[*it]);
	}
	
	
	
	for (std::vector<ServerConfig>::iterator it = configs.begin(); it < configs.end(); ++it) {
		try {
			servers.push_back(new Server(*it));
		}
		catch (const std::invalid_argument& e) {
			serverClear(0);
		}
	}

	//initialize the server operations manager from the servers vector
	Manager serverManager(servers);

	//run it all
	serverManager.loop();

	for (std::deque<Server*>::iterator it = servers.begin(); it < servers.end(); ++it) {
		delete *it;
	}
	return (0);
}