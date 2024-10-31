#ifndef SERVER_HPP
# define SERVER_HPP

# include "ListenSocket.hpp"
# include "Client.hpp"
# include <iostream>
# include <ctime>
# include <unistd.h>
# include <vector>
# include <sys/select.h>
# include "../../includes/webserv.hpp"
# include "SERVERCONFIG_PATH" //



class Server {
	public:
		Server(ServerConfig config, int domain, int service, int protocol, int port, u_long interface, int backlog);
		Server(ServerConfig config);
		~Server(void);

		ListenSocket * getListenSocket(void) const ;
		std::vector<int> getActiveConnections(void) const;
	
		Client listenNewConnections(void) ;
		void readSocket(Client &client);
		void writeSocket(Client &client, std::string msg);

	private:
		void closeConnection(Client &client);
		// void checkIdleClient(Client &client);

		ServerConfig 			_config;
		ListenSocket *			_listenSocket;
		std::vector<int>		_activeConnections;
};

#endif