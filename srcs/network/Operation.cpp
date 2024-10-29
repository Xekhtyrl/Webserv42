#include "Operation.hpp"

Operation::Operation(int sock, Server &server) _sock(sock), _server(server) {

}

int Operation::getSock(void) const {
	return _sock;
}
Client Operation::getClient(void) const {
	return _client;
}