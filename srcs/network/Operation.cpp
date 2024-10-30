#include "Operation.hpp"

Operation::Operation(int sock, Server &server, char type): _sock(sock), _server(server), _type(type) {

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