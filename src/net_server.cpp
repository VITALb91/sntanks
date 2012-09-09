#include "../include/net_server.h"

net_server::net_server()
{
}

net_server::~net_server()
{
	clients.clear();
	close(listener);
}

bool net_server::Init(int port)
{
	struct sockaddr_in addr;
	
	listener = socket(AF_INET, SOCK_STREAM, 0);
    if( (listener = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Server initiation error\n");
        return false;
    }
    
    fcntl(listener, F_SETFL, O_NONBLOCK);
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    
    if( bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        printf("Server bind adress error\n");
        return false;
    }

    listen(listener, 4);
    
    clients.clear();
    
    return true;
}

void net_server::StartListening(void)
{
	printf("Network server started at port...\n");
	connected = true;
	
	while(connected)
    {
        fd_set readset;
        FD_ZERO(&readset);
        FD_SET(listener, &readset);

        for(set<int>::iterator it = clients.begin(); it != clients.end(); it++)
			FD_SET(*it, &readset);

        timeval timeout;
        timeout.tv_sec = 600;
        timeout.tv_usec = 0;

        // Waiting for socket event
        int mx = max(listener, *max_element(clients.begin(), clients.end()));
        if(select(mx+1, &readset, NULL, NULL, &timeout) <= 0)
        {
            //printf("Select readsocket error\n");
            //connected = false;
            printf("No client activity after 10 minutes\nServer is empty\n");
            continue;
        }
        
        // Check the event
        if(FD_ISSET(listener, &readset))
        {
            // New connection
            int sock = accept(listener, NULL, NULL);
            if(sock < 0)
            {
                printf("Accept new connection error\n");
                connected = false;
            }
            
            fcntl(sock, F_SETFL, O_NONBLOCK);

            clients.insert(sock);
        }

        for(set<int>::iterator it = clients.begin(); it != clients.end(); it++)
        {
            if(FD_ISSET(*it, &readset))
            {
				/*
					Processing server netwok
					
					Now example echo-server: send back client message
					
					TODO: transfer and receiving (processing) game data
				*/
				
                // new data from client
                
                bytes_read = recv(*it, buf, 1024, 0);

                if(bytes_read <= 0)
                {
                    // Client connection close, remove him from list
                    close(*it);
                    clients.erase(*it);
                    continue;
                }

                // Test: send message back to client
                send(*it, buf, bytes_read, 0);
            }
        }
    }
    connected = false;
}

bool net_server::get_status(void)
{
	return connected;
}
	
	
	
