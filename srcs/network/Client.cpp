#include "Client.hpp"

Client::Client(int sock): _sock(sock) {
	updateLastActiveTime();
	_isClient = true;
	_isAlive = true;
}

int Client::getSock(void) const {
	return _sock;
}
time_t Client::getLastActiveTime(void) const {
	return _lastActiveTime;
}
std::vector<unsigned char> Client::getReadBuffer(void) const {
	return _readBuffer;
}
unsigned char * Client::getWriteBuffer(void) const {
	return (unsigned char *)_writeBuffer.data();
}
int Client::getWriteBufferSize(void) const {
	return _writeBuffer.size();
}
bool Client::getIsAlive(void) const {
	return _isAlive;
}
bool Client::getIsClient(void) const {
	return _isClient;
}


void Client::updateLastActiveTime(void) {
	_lastActiveTime = std::time(NULL);
}
void Client::kill(void) {
	_isAlive = false;
}

void Client::appendReadBuffer(char *readBuffer[BUFFER_SIZE], int received) {
	_readBuffer.insert(_readBuffer.end(), *readBuffer, *readBuffer + received);
}

void Client::clearReadBuffer(void) {
	_readBuffer.clear();
}
void Client::clearWriteBuffer(void) {
	_writeBuffer.clear();
}
void Client::clearWriteBuffer(int size) {
	_writeBuffer.erase(_writeBuffer.begin(), _writeBuffer.begin() + size);
}