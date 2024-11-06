#pragma once

//# include "../network.hpp"
#include "Server.hpp"
#include "Operation.hpp"
#include <vector>
#include <queue>

class Operation;
class Server;

class Manager {
	public:
		Manager(std::vector<Server *> servers);
		~Manager(void);
		void loop(void);

	private:
		void checkSockets(void);
		void processHeadOperation(void);
		void handleNewConnection(Operation op);
		void handleRead(Operation op);
		void handleWrite(Operation op);

		std::queue<Operation>	_queue;
		std::vector<Server *>	_servers;
		std::vector<int>		_activeConnections;
		fd_set					_readFds;
		fd_set					_writeFds;
		struct timeval			_selectTimeout;
};