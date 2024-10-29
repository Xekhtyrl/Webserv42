#include "Client.hpp"

Client::Client(int sock, Server &server): _sock(sock), _server(server) {
	updateLastActiveTime();
}

int Client::getSock(void) const {
	return _sock;
}
time_t Client::getLastActiveTime(void) const {
	return _lastActiveTime;
}

void Client::updateLastActiveTime(void) {
	_lastActiveTime = std::time(NULL);
}

void Client::append(char &readBuffer[BUFFER_SIZE], int received) {
	_buffer.insert(_buffer.end(), readBuffer, readBuffer + received);
}

void Client::clearBuffer(void) {
	_buffer.clear();
}