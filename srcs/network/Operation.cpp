#include "Operation.hpp"

Operation::Operation(void) {
	_client = NULL;
	_server = NULL;
}

Operation::Operation(Client *client, int sock, Server *server, char type): _server(server), _type(type) {
	_client = client;
	_sock = sock;
}

Operation::Operation(int sock, Server *server, char type): _server(server), _type(type) {
	_client = NULL;
	_sock = sock;
}

Operation& Operation::operator=(const Operation &op) {
	_sock = op.getSock();
	_client = op.getClient();
	_server = op.getServer();
	_type = op.getType();
	return *this;
}

Operation::~Operation(void) {
	//deal with delete
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
