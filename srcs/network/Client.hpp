#pragma once

# include "../../includes/webserv.hpp"
//#include "../network.hpp"
#define BUFFER_SIZE 1024
#include <ctime>
#include <vector>
#include <string>

class Client {
	public:
		Client(int sock);
		int getSock(void) const;
		// time_t getLastActiveTime(void) const;
		unsigned char* getWriteBuffer(void) const;
		int getWriteBufferSize(void) const;
		std::vector<unsigned char> getReadBuffer(void) const;
		bool getIsAlive(void) const;

		// void updateLastActiveTime(void);
		void kill(void);
		void appendReadBuffer(char *readBuffer[BUFFER_SIZE], int received);
		void appendWriteBuffer(std::string response);
		void appendWriteBuffer(std::vector<unsigned char> response);
		void appendWriteBuffer(char *response);

		void clearReadBuffer(void);
		void clearWriteBuffer(void);
		void clearWriteBuffer(int size);
		bool	_delete;

	private:
		int _sock;
		std::vector<unsigned char> _readBuffer;
		std::vector<unsigned char> _writeBuffer;
		// time_t	_lastActiveTime;
		bool	_isAlive;
};
