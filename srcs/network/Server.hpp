#ifndef SERVER_HPP
# define SERVER_HPP

# include "ListenSocket.hpp"
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


class Server {
	public:
		Server(ServerConfig config, int domain, int service, int protocol, int port, u_long interface, int backlog);
		Server(ServerConfig config);
		~Server(void);

		ListenSocket * getSocket(void) const ;
		
		void loop(int n_loops);
		void sendFileContent(int sock, std::string path);
		void sendResponse(int sock, std::string response);
	
	private:
		void listenNewConnections(void) ;
		void removeConnection(int socket);
		void processReadQueue(void);
		void processWriteQueue(void);
		void writeSocket(int sock, std::string msg);
		void readSocket(int sock);
		void checkSockets(void);
		void checkIdleClients(void);
		void updateLastActiveTime(int sock);

		//tmp
		void parsing_CGI_response(int sock, std::string rawRequest);
		
		
		
		ServerConfig 			_config;
		ListenSocket *			_listenSocket;
		char 						_buffer[BUFFER_SIZE];
		std::string					_rawClientReq;
		std::vector<int>		_activeConnections; //vecteur des connections clients ouvertes
		std::map<int, time_t>	_lastActiveTime;
		std::queue<int>								_readQueue; //queue d'attente de lecture de sockets
		std::queue<std::pair<int, std::string> >	_writeQueue; //int: numero socket. string: HTTP response
		fd_set					_readFds;
		fd_set					_writeFds;
		int						_max_fd;
};

#endif