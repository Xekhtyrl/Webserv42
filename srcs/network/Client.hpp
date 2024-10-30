#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <vector>
#include "Server.hpp"

class Client {
	public:
		Client(int sock, Server& server);

		int getSock(void) const; //done
		time_t getLastActiveTime(void) const; //done
		char* getWriteBuffer(void); //done
		int getWriteBufferSize(void) const; //done
		std::vector<unsigned char> getReadBuffer(void);

		void updateLastActiveTime(void); //done
		void appendReadBuffer(char &readBuffer[BUFFER_SIZE], int received); //done
		void appendWriteBuffer(std::string response);
		void appendWriteBuffer(std::vector<unsigned char> response);
		void appendWriteBuffer(char *response);

		void clearReadBuffer(void); //done
		void clearWriteBuffer(void); //done
		void clearWriteBuffer(int size); //done

	private:
		int _sock;
		Server _server;
		std::vector<unsigned char> _readBuffer;
		std::vector<unsigned char> _writeBuffer;
		time_t _lastActiveTime;
};


#endif