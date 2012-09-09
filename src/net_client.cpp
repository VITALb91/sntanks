#include "../include/net_client.h"
    
net_client::net_client(void)
{
}

net_client::~net_client(void)
{
	close(sock);
}

bool net_client::Connect(char *hostname, int port)
{
	struct sockaddr_in addr;

    if( (sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Client initiate error\n");
        return false;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(hostname);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        printf("Connection error\n");
        return false;
    }
    connected = true;
    
    return true;
}

void net_client::StartTransmitting(void)
{
	/*
		Processing client netwok
		
		Now example echo-client: send message[] to server every 5 second and get it back
		
		TODO: transfer and receiving (processing) game data
	*/
	
	char message[] = "Echo from server test success!\n";
	char buf[sizeof(message)];
	
	while(true)
	{
		send(sock, message, sizeof(message), 0);
		recv(sock, buf, sizeof(message), 0);
		printf(buf);
		sleep(5);
	}
}

bool net_client::get_status(void)
{
	return connected;
}
