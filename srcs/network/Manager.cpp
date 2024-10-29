#include "Manager.hpp"

Manager::Manager(void) {
	_selectTimeout.tv_sec = 0; _selectTimeout.tv_usec = 50000; //0.05 second
}

Manager::~~Manager(void) {
	delete servers;
}

void Manager::loop(void) {
	checkSockets();
	processHeadOperation();
	//once in a while sanitize check for idle connection
}

void Manager::processHeadOperation(void) {
	Operation operation;
	while (true) { //can fuck up. Limit later
		operation = _queue.front();
		_queue.pop();
		_queue.push(operation);
		if (FD_ISSET(operation.getSock())) {
			execute_operation(); ////////
			break ;
		}
	}
}

void Manager::checkSockets(void) { 
	//clear fd_sets before every select
	FD_ZERO(&_readFds);
	FD_ZERO(&_writeFds);
	//add all sockets from all servers into read & write sets
	for (std::vector<Server>::iterator server = _servers.begin(); server < _servers.end(); ++server) {
		FD_SET(server->getlistenSocket()->getSocket(), &_readFds);
		for (std::vector<int>::iterator it = server->getActiveConnections().begin(); it < server->getActiveConnections().end(); ++it) {
			FD_SET(*it, &_writeFds);
			FD_SET(*it, &_readFds);
		}
	}
	if (select(_maxFd + 1, &_readFds, &_writeFds, NULL, _selectTimeout) < 0 && errno != EINTR) //EINTR = caught signal
		perror("error: select(): ");
}
