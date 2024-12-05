#include "Manager.hpp"

Manager::Manager(std::vector<Server *> servers): _servers(servers) {
	_selectTimeout.tv_sec = 0; _selectTimeout.tv_usec = 50000; //0.05 second
	//initialize the queue with listening sockets for new connections
	for (std::vector<Server *>::iterator server = _servers.begin(); server < _servers.end(); ++server) {
		_queue.push(Operation(NULL, (*server)->getListenSocket()->getSocket(), *server, 'l'));
	}
}

Manager::~Manager(void) {}

void Manager::loop(void) {
	while (true) {
		checkSockets();
		processHeadOperation();
	}
}

void Manager::checkSockets(void) { 
	int maxFd = 0;
	std::vector<int>serverActiveConnections;
	//clear fd_sets before every select
	FD_ZERO(&_readFds);
	FD_ZERO(&_writeFds);
	//add all sockets from all servers into read & write sets
	//at the same time save the maxFd value, as required by select()
	for (std::vector<Server *>::iterator server = _servers.begin(); server < _servers.end(); ++server) {
		if (maxFd < (*server)->getListenSocket()->getSocket())
			maxFd = (*server)->getListenSocket()->getSocket();
		FD_SET((*server)->getListenSocket()->getSocket(), &_readFds);
		serverActiveConnections = (*server)->getActiveConnections();
		for (std::vector<int>::iterator it = serverActiveConnections.begin(); it < serverActiveConnections.end(); ++it) {
			if (maxFd < *it)
				maxFd = *it;
			FD_SET(*it, &_writeFds);
			FD_SET(*it, &_readFds);
		}
	}
	if (select(maxFd + 1, &_readFds, &_writeFds, NULL, &_selectTimeout) < 0 && errno != EINTR) //EINTR = caught signal
		perror("error: select(): ");
}

void Manager::processHeadOperation(void) {
	Operation	op;
	bool		nothingExecuted = true;
	int			queueSize = _queue.size();
	Client*		client;
	//execute the first operation in the queue.
	//if the operation's socket isn't ready for the writing or reading,
	//put it at the back of the queue and try the next operation.
	//Stop if you have cycled through the whole queue to make a new select() call
	while (nothingExecuted && queueSize--) {
		op = _queue.front();
		_queue.pop();
		client = op.getClient();
		if (client == NULL || client->getIsAlive()) {
			_queue.push(op);
			nothingExecuted = false;
			if (op.getType() == 'l' && FD_ISSET(op.getSock(), &_readFds))
				handleNewConnection(op);	//2 operations creation: read socket and write socket
			else if (op.getType() == 'r' && FD_ISSET(op.getSock(), &_readFds))
				handleRead(op);				//read operation execution
			else if (op.getType() == 'w' && FD_ISSET(op.getSock(), &_writeFds) && client->getWriteBufferSize())
				handleWrite(op);			//write operation execution
			else
				nothingExecuted = true;
		}
		else if (client != NULL) {
			if (client->_delete == true)
				delete 	client;
			else
				client->_delete = true;
		}
	}
}

void Manager::handleNewConnection(Operation op) {
	Client* newClient = op.getServer()->listenNewConnections();
	if (!newClient) {
		//error
		return;
	}
	//if new client connection was done by server,
	//add both read and write operations of that client into the queue
	_queue.push(Operation(newClient, newClient->getSock(), op.getServer(), 'r'));
	_queue.push(Operation(newClient, newClient->getSock(), op.getServer(), 'w'));
}
void Manager::handleRead(Operation op) {
	op.getServer()->readSocket(op.getClient());
}
void Manager::handleWrite(Operation op) {
	op.getServer()->writeSocket(op.getClient());
}




//need to turn the &client into *client in operations. Check where the clients are created. new. ?