#ifndef CLIENT_HPP
# define CLIENT_HPP


# include <vector>
# include <string>
# include <iostream> //?
# include <ctime>
# include "Server.hpp"

class Client {
	public:
		Client(int sock, Server& server);

		int getSock(void) const; //done
		time_t getLastActiveTime(void) const; //done
		char* getWriteBuffer(void); //done
		int getWriteBufferSize(void) const; //done
		std::vector<char> getReadBuffer(void);

		void updateLastActiveTime(void); //done
		void kill(void); //done
		void appendReadBuffer(char &readBuffer[BUFFER_SIZE], int received); //done
		void appendWriteBuffer(std::string response);
		void appendWriteBuffer(char *response);

		void clearReadBuffer(void); //done
		void clearWriteBuffer(void); //done
		void clearWriteBuffer(int size); //done

	private:
		int _sock;
		Server _server;
		std::vector<char> _readBuffer;
		std::vector<char> _writeBuffer;
		time_t	_lastActiveTime;
		bool	_isAlive;

};


#endif