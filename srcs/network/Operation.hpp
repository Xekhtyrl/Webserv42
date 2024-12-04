#pragma once

#include "Server.hpp"
#include "Client.hpp"


class Server;
class Client;

class Operation {
	public:
		Operation(void);
		Operation(Client *client, int sock, Server* server, char type); //Client read or write
		Operation& operator=(const Operation &op);
		~Operation(void);
		int getSock(void) const;
		Client* getClient(void) const ;
		Server* getServer(void) const;
		char getType(void) const;

	private:
		int		_sock;
		Client 	*_client;
		Server	*_server;
		char	_type;		//listen, read, or write
};
