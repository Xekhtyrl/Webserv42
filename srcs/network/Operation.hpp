#ifndef OPERATION_HPP
# define OPERATION_HPP

class Operation {
	public:
		Operation(int sock, Server& server);
		int getSock(void) const;
		Client getClient(void) const ;
	private:
		int _sock;
		Client _client
		Server _server

	
};

#endif