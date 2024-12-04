#pragma once

#include "ListenSocket.hpp"
#include "Client.hpp"
#include "../../includes/webserv.hpp"
#include "../Configuration/ServerConfig.hpp"
// # include "SERVERCONFIG_PATH" //

class Client;
class ServerConfig;
class ListenSocket;

class Server {
	public:
		// Server();
		Server(ServerConfig config, int domain, int service, int protocol, u_long interface, int backlog);
		Server(ServerConfig config);
		// Server(const Server &other); //can't have two servers on the same port
		// Server &operator=(const Server &rhs); //idem. Sorry Orthodox
		~Server(void);

		ListenSocket * getListenSocket(void) const ;
		std::vector<int> getActiveConnections(void) const;
	
		Client* listenNewConnections(void) ;
		void readSocket(Client *client);
		void writeSocket(Client *client);

	private:
		void closeConnection(Client *client);
		// void checkIdleClient(Client &client);

		ServerConfig 			_config;
		ListenSocket *			_listenSocket;
		std::vector<int>		_activeConnections;
		char *					_buffer;
};
