#include "../include/gameCore.h"
#include <string.h>

int main(int argc, char **argv)
{
	int port;
	gameCore tanks;
	
	switch(argc)
	{
		case 2:
			// server
			port = atoi(argv[1]);
			if (!tanks.Init(800,600,32,NULL,port)) return -1;
			break;
			
		case 3:
			// client
			port = atoi(argv[1]);
			if (!tanks.Init(800,600,32,argv[2],port)) return -1;
			break;
			
		default:
			printf("Uses %s port [hostname]\nIf no hostname - mode=server, else mode=client\n",argv[0]);
			break;
	}

	tanks.Start();
	return 0;
}
