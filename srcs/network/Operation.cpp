#include "Operation.hpp"

Operation::Operation(void) {
	_client = NULL;
	_server = NULL;
}

Operation::Operation(Client *client, int sock, Server *server, char type): 
	_sock(sock), _client(client), _server(server), _type(type) {}

Operation& Operation::operator=(const Operation &op) {
	_sock = op.getSock();
	_client = op.getClient();
	_server = op.getServer();
	_type = op.getType();
	return *this;
}

Operation::~Operation(void) {
	//_client is dynamically allocated, with 2 pointers kept in 2 Operations.
	//Only when the first Operation is destroyed can the second Operation delete _client
	if (_client->_delete == true)
		delete _client;
	else
		_client->_delete = true;
}

int Operation::getSock(void) const {
	return _sock;
}
Client* Operation::getClient(void) const {
	return _client;
}
Server* Operation::getServer(void) const {
	return _server;
}
char Operation::getType(void) const {
	return _type;
}
