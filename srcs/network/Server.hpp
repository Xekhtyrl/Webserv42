#ifndef SERVER_HPP
# define SERVER_HPP

# include "ListenSocket.hpp"
# include "Client.hpp"
# include <iostream>
# include <ctime>
# include <unistd.h>
# include <vector>
# include <algorithm>
# include <sys/select.h>
# include "../../includes/webserv.hpp"
# include <iostream>
# include <stdio.h>
# include <sys/socket.h>
# include <unistd.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <string>
# include <fstream>
# include <vector>
# include <dirent.h>
# include <exception>
# include <map>
# include <sstream>
# include "../HTTPProtocol/HTTPRequest.hpp"
# include "../HTTPProtocol/HTTPReponse.hpp"
# include "../network/ASocket.hpp"
# include "BindSocket.hpp"
# include "ConnectSocket.hpp"
# include "ListenSocket.hpp"
# include "Server.hpp"
# include "Client.hpp"
# include "../Configuration/Config.hpp"
# include "../Configuration/RouteConfig.hpp"
# include "../Configuration/ServerConfig.hpp"
// # include "SERVERCONFIG_PATH" //

class Client;
class ServerConfig;
class ListenSocket;

class Server {
	public:
		Server();
		Server(ServerConfig config, int domain, int service, int protocol, int port, u_long interface, int backlog);
		Server(ServerConfig config);
		Server(const Server &other);
		Server &operator=(const Server &rhs);
		~Server(void);

		ListenSocket * getListenSocket(void) const ;
		std::vector<int> getActiveConnections(void) const;
	
		Client listenNewConnections(void) ;
		void readSocket(Client &client);
		void writeSocket(Client &client);

	private:
		void closeConnection(Client &client);
		// void checkIdleClient(Client &client);

		ServerConfig 			_config;
		ListenSocket *			_listenSocket;
		std::vector<int>		_activeConnections;
		char *					_buffer;
};

#endif
