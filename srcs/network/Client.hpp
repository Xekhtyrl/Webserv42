#pragma once

//# include "../../includes/webserv.hpp"
//#include "../network.hpp"
#define BUFFER_SIZE 1024
#include <ctime>
#include <vector>
#include <string>

class Client {
	public:
		Client(int sock);
		int getSock(void) const; //done
		time_t getLastActiveTime(void) const; //done
		unsigned char* getWriteBuffer(void) const; //done
		int getWriteBufferSize(void) const; //done
		std::vector<unsigned char> getReadBuffer(void) const;
		bool getIsAlive(void) const;

		void updateLastActiveTime(void); //done
		void kill(void); //done
		void appendReadBuffer(char *readBuffer[BUFFER_SIZE], int received); //done
		void appendWriteBuffer(std::string response);
		void appendWriteBuffer(std::vector<unsigned char> response);
		void appendWriteBuffer(char *response);

		void clearReadBuffer(void); //done
		void clearWriteBuffer(void); //done
		void clearWriteBuffer(int size); //done
		bool	_delete;

	private:
		int _sock;
		std::vector<unsigned char> _readBuffer;
		std::vector<unsigned char> _writeBuffer;
		time_t	_lastActiveTime;
		bool	_isAlive;
};
