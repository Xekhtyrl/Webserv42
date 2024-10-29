#ifndef MANAGER_HPP
# define MANAGER_HPP

#include <iostream>

class Manager {
	public:
		Manager(void);
		~Manager(void);
		void loop(void);
		void checkSockets(void);

	private:
		std::queue<Operation>	_queue;
		std::vector<Server>		_servers;

		std::vector<int>		_activeConnections;

		fd_set					_readFds;
		fd_set					_writeFds;
		int						_maxFd
		struct timeval			_selectTimeout;
};

#endif