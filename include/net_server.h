#ifndef __net_server_H__
#define __net_server_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <fcntl.h>
#include <algorithm>
#include <set>

using namespace std;

class net_server
{
	private:
	
	int listener;
	set<int> clients;
	
	char buf[1024];
    int bytes_read;
    
    bool connected;
	
	public:
	net_server();
	~net_server();
	bool Init(int port);
	void StartListening(void);
	bool get_status(void);
};

#endif
