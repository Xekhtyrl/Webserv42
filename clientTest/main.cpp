#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Client.hpp"

int main(int argc, char **argv) {

	int n_clients = 10;	//atoi(argv[1]);

	Client* clients = new Client[n_clients]; //port 8080 par défaut
    for (int i=0; i < n_clients; ++i) {
		clients[i].talk(1);
	}
	delete[] clients;
	
    return 0;
}
