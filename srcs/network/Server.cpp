#include "Server.hpp"

Server::Server(int domain, int service, int protocol, int port, u_long interface, int backlog, std::string name) {
	_listenSocket = new ListenSocket(domain, service, protocol, port, interface, backlog);
	_name = name;
	_max_fd = _listenSocket->getSocket();
	std::cout << "Listening to new connections on port " << ntohs(_listenSocket->getAddress().sin_port) << std::endl;
}
Server::Server(int port, std::string name) {
	_listenSocket = new ListenSocket(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY, 20);
	_name = name;
	_max_fd = _listenSocket->getSocket();
	std::cout << "Listening to new connections on port " << ntohs(_listenSocket->getAddress().sin_port) << std::endl;
}


Server::~Server(void) {
	close(_listenSocket->getSocket());
	delete _listenSocket;
}

void Server::launch(void) {
	while (true) {
		listenNewConnections(); //Single listen and accept per loop, do we need more?
		processWriteQueue(); 
		processReadQueue();
	}
}

void Server::processWriteQueue(void) {
	std::pair<int, std::string> sock;
	int queueSize = _writeQueue.size();
	for (int i=0; i < queueSize; ++i) {
		sock = _writeQueue.front();
		_writeQueue.pop();
	 	checkSockets();
		if (FD_ISSET(sock.first, &_writeFds)) { //always check the socket is ready for writing
			writeSocket(sock.first, sock.second); //!
		}
		else 
			_writeQueue.push(sock); //Socket not ready for writing, try again? Try counter?
	}
}

void Server::writeSocket(int sock, std::string msg) {
	if (write(sock, msg.c_str(), msg.length()) < 0) {
		removeConnection(sock);
	}
}

ListenSocket* Server::getSocket(void) const {
	return _listenSocket;
}

void Server::checkSockets(void) { //to be called before EVERY read or write.
	FD_ZERO(&_readFds); // man said it's necessary to reinitialize the fd_sets
	FD_ZERO(&_writeFds); //before every select() call
	FD_SET(_listenSocket->getSocket(), &_readFds);
	for (std::vector<int>::iterator it = _activeConnections.begin(); it < _activeConnections.end(); ++it) {
		FD_SET(*it, &_writeFds);
		FD_SET(*it, &_readFds);
	}
	if (select(_max_fd + 1, &_readFds, &_writeFds, NULL, NULL) < 0 && errno != EINTR) { //EINTR = caught signal
		perror("error: select(): ");
	}
}

void parse_buffer_to_find_message_size_to_then_read_the_missing_data(int sock) {
	std::cout << "Client " << sock << " sent a big message" << std::endl;
	(void)sock;
}

void Server::readSocket(int sock) {
	memset(_buffer, 0, BUFFER_SIZE);
	int received = read(sock, _buffer, BUFFER_SIZE); //lecture avec buffer conséquent, normal.
	if (received <= 0) {
		if (received == 0)
			std::cout << "Client " << sock << " closed the connection gracefully" << std::endl;
		removeConnection(sock); //pas certain de la gestion des mauvais read (< 0). On kill la connection?
	}
	else if (received == BUFFER_SIZE) { //si le buffer statique n'était pas suffisant pour tout le message, 
		parse_buffer_to_find_message_size_to_then_read_the_missing_data(sock);
		//nécessite soit une fonction de parsing attitrée,
		//soit un flag dans le parseur indiquant qu'il faut read+concaténer de message_size - BUFFER_SIZE
	}
	else {
		std::string rawRequest(_buffer);
		std::cout << "Client " << sock << ":" << std::endl << rawRequest << std::endl;
		parsing_CGI_response(sock, rawRequest); //this function then adds the response to the _writeQueue
	}
}

void Server::processReadQueue(void) {
	int sock;
	for (std::vector<int>::iterator it = _activeConnections.begin(); it < _activeConnections.end(); ++it) {
		_readQueue.push(*it); //for now queue unnecessary with that approach. _activeConnections enough
	}
	int queueSize = _readQueue.size();
	for (int i=0; i < queueSize; ++i) {
		sock = _readQueue.front();
		_readQueue.pop();
		checkSockets();
		if (FD_ISSET(sock, &_readFds)) {
			readSocket(sock); //!
		}
	}
}

void Server::listenNewConnections(void) {
	checkSockets();
	if (FD_ISSET(_listenSocket->getSocket(), &_readFds)) {
		struct sockaddr_in address = _listenSocket->getAddress();
		socklen_t socketLength = static_cast<socklen_t>(sizeof(address));
		int newClientSocket = accept(_listenSocket->getSocket(), (struct sockaddr *)&address, &socketLength);
		if (newClientSocket < 0)
			perror("error: select(): ");
		else {
			FD_SET(newClientSocket, &_readFds);
			FD_SET(newClientSocket, &_writeFds);
			_activeConnections.push_back(newClientSocket);
			if (newClientSocket > _max_fd)
				_max_fd = newClientSocket;
			std::cout << "New socket on fd: " << newClientSocket << std::endl;
		}
	}
}

void Server::removeConnection(int socket) {
	close(socket);
	FD_CLR(socket, &_writeFds);
	FD_CLR(socket, &_readFds);
	std::vector<int>::iterator it = std::find(_activeConnections.begin(), _activeConnections.end(), socket);
    if (it != _activeConnections.end()) {
        _activeConnections.erase(it);
    }
	std::cout << "Removed connection on socket " << socket << std::endl;
}


void Server::parsing_CGI_response(int sock, std::string rawRequest) {
	_writeQueue.push(std::make_pair(sock, "*" + _name + " response* [" + rawRequest + "]"));
}