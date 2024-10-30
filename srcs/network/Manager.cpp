#include "Manager.hpp"

Manager::Manager(std::vector<Server> servers): _servers(servers) {
	_selectTimeout.tv_sec = 0; _selectTimeout.tv_usec = 50000; //0.05 second
}

Manager::~~Manager(void) {
	delete servers;
}

void Manager::loop(void) {
	checkSockets();
	processHeadOperation();
	sanitize();
}

void Manager::checkSockets(void) { 
	int maxFd = 0;
	//clear fd_sets before every select
	FD_ZERO(&_readFds);
	FD_ZERO(&_writeFds);
	//add all sockets from all servers into read & write sets
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
	Operation operation;
	while (true) { //can fuck up. Limit later
		op = _queue.front();
		_queue.pop();
		_queue.push(op);
		if (FD_ISSET(op.getSock())) {
			execute_op(); ////////
			switch (op.getType()) {
				case 'l':
					handleNewConnection(op);
				case 'r':
					handleRead(op);
				case 'w':
					handleWrite(op);
			}
			break ;
		}
	}
}

void Manager::handleNewConnection(Operation op) {
	Client newClient = op.getServer().listenNewConnections();
	if (newClient == NULL) {
		//error
		return;
	}
	_queue.push(Operation(newClient.getSock(), op.getServer(), 'r'));
	_queue.push(Operation(newClient.getSock(), op.getServer(), 'w'));
}
void Manager::handleRead(Operation op) {
	op.getServer().readSocket(op.getClient());
}
void Manager::handleWrite(Operation op) {
	op.getServer().writeSocket(op.getClient());
}

void Manager::sanitize(void) {
	for (std::vector<Server>::iterator server = _servers.begin(); server < _servers.end(); ++server) {
		if (!it->getClosedConnections().empty())
			removeClientOperations(it->getClosedConnections())
	}
	//need to remove operations from the queue when a client connection is Closed
	//the issue being that Servers don't yet have the reference of the queue
}

void Manager::removeClientsOperations(std::queue<int> closedQueue) {
	//loop through queue and remove clients

	//maybe ineficient? Should I check in the checkSocket FD_ISSET false?
}