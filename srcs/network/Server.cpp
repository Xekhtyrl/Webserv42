#include "Server.hpp"

Server::Server(ServerConfig config, int domain, int service, int protocol, u_long interface, int backlog) {
	_listenSocket = new ListenSocket(domain, service, protocol, config->getPort(), interface, backlog);
	_max_fd = _listenSocket->getSocket();
	std::cout << "Listening to new connections on port " << ntohs(_listenSocket->getAddress().sin_port) << std::endl;
}
Server::Server(ServerConfig config) {
	_listenSocket = new ListenSocket(AF_INET, SOCK_STREAM, 0, config->getPort(), INADDR_ANY, 20);
	_max_fd = _listenSocket->getSocket();
	std::cout << "Listening to new connections on port " << ntohs(_listenSocket->getAddress().sin_port) << std::endl;
}

Server::~Server(void) {
	close(_listenSocket->getSocket());
	delete _listenSocket;
}

void Server::loop(int n_loops) {
	while (n_loops--) {
		listenNewConnections(); //Single listen and accept per loop, do we need more?
		processWriteQueue(); 
		processReadQueue();
		checkIdleClients();
	}
}

void Server::sendResponse(int sock, std::string response) {
	_writeQueue.push(std::pair<int, std::string>(sock, response));
}

void sendFileContent(int sock, std::string path) {
	std::string fileCont = getFileContent();
	sendResponse(sock, fileCont);
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
			_activeConnections.push_back(newClientSocket);
			_lastActiveTime.insert(std::map<int, time_t>::value_type(newClientSocket, std::time(NULL)));
			if (newClientSocket > _max_fd)
				_max_fd = newClientSocket;
			std::cout << "New socket on fd: " << newClientSocket << std::endl;
		}
	}
}

void Server::processWriteQueue(void) {
	std::pair<int, std::string> sock;
	int queueSize = _writeQueue.size();
	for (int i=0; i < queueSize; ++i) {
		sock = _writeQueue.front();
		_writeQueue.pop();
		FD_SET(sock.first, &_writeFds);
	 	checkSockets();
		if (FD_ISSET(sock.first, &_writeFds)) { //always check the socket is ready for writing
			writeSocket(sock.first, sock.second); //!
			FD_CLR(sock.first, &_writeFds);
		}
		else 
			_writeQueue.push(sock); //Socket not ready for writing, try again? Try counter?
	}
}

void Server::writeSocket(int sock, std::string msg) {
	if (write(sock, msg.c_str(), msg.length()) < 0)
		removeConnection(sock);
	else
		updateLastActiveTime(sock);
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
	if (select(_max_fd + 1, &_readFds, &_writeFds, NULL, NULL) < 0 && errno != EINTR) //EINTR = caught signal
		perror("error: select(): ");
}
void Server::checkIdleClients(void) {
	time_t now = std::time(NULL);
	for (std::map<int, time_t>::iterator it = _lastActiveTime.begin(); it != _lastActiveTime.end(); ++it) {
		if (it->second + IDLE_TIMEOUT < now) {
			removeConnection(it->first);
			--it;
		}
	}
}

void Server::readSocket(int sock) {
	size_t received = BUFFER_SIZE;
	_rawClientReq = "";
	while (received == BUFFER_SIZE) {
		memset(_buffer, 0, BUFFER_SIZE);
		checkSockets();
		if (FD_ISSET(sock, &_readFds)) {
			received = read(sock, _buffer, BUFFER_SIZE);
			updateLastActiveTime(sock);
			_rawClientReq.append(_buffer, received);
		}
		else
			return;
	}
	if (received <= 0) //if < 0: error. else if == 0: EOF from client
		removeConnection(sock); //pas certain de la gestion des mauvais read (< 0). On kill la connection?
	else 
		sendResponse(sock, requestToResponseProcess(&_rawRequest, _config));
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
		readSocket(sock);
	}
}

void Server::updateLastActiveTime(int sock) {
	_lastActiveTime[sock] = std::time(NULL);
}
void Server::removeConnection(int socket) {
	close(socket);
	FD_CLR(socket, &_writeFds);
	FD_CLR(socket, &_readFds);
	std::vector<int>::iterator it_1 = std::find(_activeConnections.begin(), _activeConnections.end(), socket);
    if (it_1 != _activeConnections.end()) {
        _activeConnections.erase(it_1);
    }
	std::map<int, time_t>::iterator it_2 = _lastActiveTime.find(socket);
    if (it_2 != _lastActiveTime.end()) {
        _lastActiveTime.erase(it_2);
    }
	std::cout << "Removed connection on socket " << socket << std::endl;
}



//should this be part of the Server function? 
void Server::parsing_CGI_response(int sock, std::string &rawRequest) {
	_writeQueue.push(std::make_pair(sock, "*" + _name + " response* [" + rawRequest + "]"));
}
