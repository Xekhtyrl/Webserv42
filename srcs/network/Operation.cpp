#include "Operation.hpp"

Operation::Operation(Client &client, int sock, Server &server, char type): _server(server), _type(type) {
	_client = client; //can be null if listening socket
	_sock = sock;
}

int Operation::getSock(void) const {
	return _sock;
}
Client Operation::getClient(void) const {
	return _client;
}
Server Operation::getServer(void) consst {
	return _server;
}
char Operation::getType(void) const {
	return _type;
}
bool Operation::getIsAlive(void) const {
	return _isAlive;
}