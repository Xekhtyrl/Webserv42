#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <vector>
#include "Server.hpp"

class Client {
	public:
		Client(int sock, Server& server);

		int getSock(void) const;
		time_t getLastActiveTime(void) const;
		char* getWriteBuffer(void);
		std::vector<unsigned char> getReadBuffer(void);

		void updateLastActiveTime(void);
		void appendReadBuffer(char &readBuffer[BUFFER_SIZE], int received);
		void appendWriteBuffer(std::string response);
		void appendWriteBuffer(std::vector<unsigned char> response);
		void appendWriteBuffer(char *response);

		void clearReadBuffer(void);
		void clearWriteBuffer(void);

	private:
		int _sock;
		Server _server;
		std::vector<unsigned char> _readBuffer;
		std::vector<unsigned char> _writeBuffer;
		time_t _lastActiveTime;
};


#endif