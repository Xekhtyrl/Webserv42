#ifndef MANAGER_HPP
# define MANAGER_HPP

#include <iostream>

class Manager {
	public:
		Manager(std::vector<Server> &servers);
		~Manager(void);
		void loop(void);

	private:
		void checkSockets(void);
		void processHeadOperation(void);
		void handleNewConnection(void);
		void handleRead(void);
		void handleWrite(void);

		std::queue<Operation>	_queue;
		std::vector<Server>		&_servers;
		std::vector<int>		_activeConnections;
		fd_set					_readFds;
		fd_set					_writeFds;
		struct timeval			_selectTimeout;
};

#endif