#include "Manager.hpp"

Manager::Manager(std::vector<Server> &servers): _servers(servers) {
	_selectTimeout.tv_sec = 0; _selectTimeout.tv_usec = 50000; //0.05 second
	//initialize the queue with listening sockets for new connections
	for (std::vector<Server>::iterator server = _servers.begin(); server < _servers.end(); ++server) {
		queue.push(Operation(NULL, it->getListenSocket().getSocket(), *it, 'l'));
	}
}

Manager::~~Manager(void) {
	delete _servers;
}

void Manager::loop(void) {
	checkSockets();
	processHeadOperation();
}

void Manager::checkSockets(void) { 
	int maxFd = 0;
	//clear fd_sets before every select
	FD_ZERO(&_readFds);
	FD_ZERO(&_writeFds);
	//add all sockets from all servers into read & write sets
	//at the same time save the maxFd value, as required by select()
	for (std::vector<Server>::iterator server = _servers.begin(); server < _servers.end(); ++server) {
		if (maxFd < server->getlistenSocket()->getSocket())
			maxFd = server->getlistenSocket()->getSocket();
		FD_SET(server->getlistenSocket()->getSocket(), &_readFds);
		for (std::vector<int>::iterator it = server->getActiveConnections().begin(); it < server->getActiveConnections().end(); ++it) {
			if (maxFd < *it)
				maxFd = *it;
			FD_SET(*it, &_writeFds);
			FD_SET(*it, &_readFds);
		}
	}
	if (select(maxFd + 1, &_readFds, &_writeFds, NULL, _selectTimeout) < 0 && errno != EINTR) //EINTR = caught signal
		perror("error: select(): ");
}

void Manager::processHeadOperation(void) {
	Operation	op;
	bool		nothingExecuted = true;
	int			queueSize = _queue.size();
	//execute the first operation in the queue.
	//if the operation's socket isn't ready for the writing or reading,
	//put it at the back of the queue and try the next operation.
	//Stop if you have cycled through the whole queue to make a new select() call
	while (nothingExecuted && queueSize--) {
		op = _queue.front();
		_queue.pop();
		if (op.getClient().getIsAlive()) {
			_queue.push(op);
			nothingExecuted = false;
			if (op.getType() == 'l' && FD_ISSET(op.getSock(), &_readFds))
				handleNewConnection(op);	//2 operations creation: read socket and write socket
			else if (op.getType() == 'r' && FD_ISSET(op.getSock(), &_readFds))
				handleRead(op);				//read operation execution
			else if (op.getType() == 'w' && FD_ISSET(op.getSock(), &_writeFds))
				handleWrite(op);			//write operation execution
			else
				nothingExecuted = true;
		}
	}
}

void Manager::handleNewConnection(Operation op) {
	Client newClient = op.getServer().listenNewConnections();
	if (newClient == NULL) {
		//error
		return;
	}
	//if new client connection was done by server,
	//add both read and write operations of that client into the queue
	_queue.push(Operation(newClient, newClient.getSock(), op.getServer(), 'r'));
	_queue.push(Operation(newClient, newClient.getSock(), op.getServer(), 'w'));
}
void Manager::handleRead(Operation op) {
	op.getServer().readSocket(op.getClient());
}
void Manager::handleWrite(Operation op) {
	op.getServer().writeSocket(op.getClient());
}
