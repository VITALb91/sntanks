#ifndef __net_client_H__
#define __net_client_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <fcntl.h>
#include <algorithm>
#include <set>

using namespace std;

class net_client
{
	private:
	int sock;
	bool connected;
	
	public:
	net_client(void);
	~net_client(void);
	bool Connect(char *hostname, int port);
	void StartTransmitting(void);
	bool get_status(void);
};

#endif
