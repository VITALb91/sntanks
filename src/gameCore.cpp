#include "../include/gameCore.h"

int StartNetwork_thread(void *data)
{
	gameCore *gc = (gameCore*) data;
	gc->NetStart();
	return 0;
}

gameCore::gameCore()
{
	game_video = NULL;
	game_network = NULL;
}

gameCore::~gameCore()
{
	SDL_Quit();
	delete game_video;
	delete game_network;
	game_video = NULL;
	game_network = NULL;
}

bool gameCore::Init(int width, int height, int bpp, char *hostname, int port)
{
	if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
	{ 
		printf("Unable to init SDL: %s\n", SDL_GetError()); 
		return false;
	}
	
	game_video = new videoCore();
	if ( !game_video || !game_video->CreateWindow(width,height,bpp,"Tanks",NULL,false) )
	{
		printf("Init video-subsystem error\n");
		return false;
	}
	
	game_network = new coreNetwork();
	if ( !game_network || !game_network->Init(hostname,port) ) 
	{
		printf("Init network-subsystem error on %s:%d\n",hostname,port);
		return false;
	}
	
	#ifdef __DEBUG_MODE__
		printf("Network subsystem initiation successful.\n");
		printf("Video subsystem initiation successful.\n");
	#endif
	
	return true;
}

void gameCore::Start()
{
	/*
		Starting all subsystems here
	*/
	
	
	// network starts at another thread
	SDL_Thread *network_thread = SDL_CreateThread( StartNetwork_thread, this);
    if ( network_thread == NULL ) 
    {
        printf("Unable to create thread: %s\n", SDL_GetError());
        return;
    }
	
	int loops = 0;
	int done = 0;
	
	long nextFrameTime = SDL_GetTicks();
	
	while(done == 0)
	{  
		loops = 0;
   
		while ( SDL_PollEvent(&game_event) )
		{ 
			if ( game_event.type == SDL_QUIT ) done = 1; 
			if ( game_event.type == SDL_KEYDOWN )
				if ( game_event.key.keysym.sym == SDLK_ESCAPE ) done = 1; 
		}
	   
		game_keys = SDL_GetKeyState(NULL);
		
		while( SDL_GetTicks() > nextFrameTime && loops < MaxFrameSkip )
		{
			playerInput();
			nextFrameTime += FrameDuration;
			loops++;
		}
		RenderScene();
	}
}

void gameCore::RenderScene()
{
	/*
		Drawing all game objects here
	*/
	game_video->SwapScreen();
}

void gameCore::NetStart(void)
{
	game_network->Start();
}

void gameCore::playerInput(void)
{
	// input listener
}
