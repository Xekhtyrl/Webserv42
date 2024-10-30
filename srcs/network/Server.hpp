#ifndef SERVER_HPP
# define SERVER_HPP

# include "ListenSocket.hpp"
# include "Client.hpp"
# include <iostream>
# include <ctime>
# include <unistd.h>
# include <vector>
# include <queue>
# include <map>
# include <sys/select.h>
# include "../../includes/webserv.h"

# define BUFFER_SIZE 1024
# define IDLE_TIMEOUT 600 //disconnects client after 10 minutes of inactivity
# define READ 1
# define WRITE 0

class Server {
	public:
		Server(ServerConfig config, int domain, int service, int protocol, int port, u_long interface, int backlog);
		Server(ServerConfig config);
		~Server(void);

		ListenSocket * getListenSocket(void) const ;
		std::vector<int> getActiveConnections(void) const;
		std::queue<int> getClosedConnections(void) const;
		
		void loop(int n_loops);
		void sendResponse(int sock, std::string response);
	
	private:
		Client listenNewConnections(void) ;
		void closeConnection(int sock);

		void writeSocket(Client client, std::string msg);
		void readSocket(Client client);
		void checkSockets(void);

		void checkIdleClient(Client client);
		void updateLastActiveTime(int sock);

		ServerConfig 			_config;
		ListenSocket *			_listenSocket;
		std::vector<int>		_activeConnections;
		std::queue<int>			_closedConnections;
};

#endif