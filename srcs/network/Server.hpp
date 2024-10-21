#ifndef SERVER_HPP
# define SERVER_HPP

# include "ListenSocket.hpp"
# include <iostream>
# include <vector>
# include <queue>
# include <sys/select.h>

# define BUFFER_SIZE 1024


class Server {
	private:
		void listenNewConnections(void) ;
		void removeConnection(int socket);
		void processReadQueue(void);
		void processWriteQueue(void);
		void writeSocket(int sock, std::string msg);
		void readSocket(int sock);
		void checkSockets(void);

		//tmp
		void parsing_CGI_response(int sock, std::string rawRequest);
		
		
		char _buffer[BUFFER_SIZE];
		
		ListenSocket * _listenSocket;
		std::vector<int> _activeConnections; //vecteur des connections clients ouvertes
		std::queue<int> _readQueue; //queue d'attente de lecture de sockets
		std::queue<std::pair<int, std::string> > _writeQueue; //int: numero socket. string: HTTP response
		fd_set	_readFds;
		fd_set	_writeFds;
		int _max_fd;
		std::string _name;



	public:
		Server(int domain, int service, int protocol, int port, u_long interface, int backlog, std::string name);
		Server(int port, std::string name);
		~Server(void);

		ListenSocket * getSocket(void) const ;
		void launch(void);
};

#endif