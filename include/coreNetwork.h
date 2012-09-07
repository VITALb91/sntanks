#ifndef __coreNetwork_H__
#define __coreNetwork_H__

#include "net_client.h"
#include "net_server.h"

class coreNetwork
{
	private:
	net_client *client;
	net_server *server;
	
	bool is_server;
	
	public:
	coreNetwork(void);
	~coreNetwork(void);
	bool Init(char *hostname, int port);
	void Start(void);
	bool get_status();
};

#endif
