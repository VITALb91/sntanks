#include "../include/coreNetwork.h"

coreNetwork::coreNetwork(void)
{
}

coreNetwork::~coreNetwork(void)
{
	if (is_server)
		delete server;
	else
		delete client;
	server = NULL;
	client = NULL;
}

bool coreNetwork::Init(char *hostname, int port)
{
	is_server = (hostname==NULL)? true : false;
	
	if (is_server)
	{
		server = new net_server();
		return server->Init(port);
	}
	else
	{
		client = new net_client();
		return client->Connect(hostname,port);
	}
}

void coreNetwork::Start(void)
{
	if (is_server)
		server->StartListening();
	else
		client->StartTransmitting();
}

bool coreNetwork::get_status()
{
	return (is_server? server->get_status() : client->get_status() );
}
