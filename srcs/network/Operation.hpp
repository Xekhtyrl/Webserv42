#ifndef OPERATION_HPP
# define OPERATION_HPP

# include "Client.hpp"
# include "Server.hpp"


class Operation {
	public:
		Operation(int sock, Server& server, char type);
		int getSock(void) const;
		Client getClient(void) const ;
		char getType(void) const;
	private:
		int		_sock;
		Client 	&_client;
		Server	&_server;
		char	_type;
};

#endif