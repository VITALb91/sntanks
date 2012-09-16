#include "../include/gameCore.h"

struct BMPfile
{
	char *filename;
} spriteFiles[MAX_PLAYERS] = { "data/Tank1.bmp", "data/Tank2.bmp", "data/Tank3.bmp", "data/Tank4.bmp" };

spriteBase TankSpriteBase[MAX_PLAYERS];

void LoadTankSprites()
{
	spriteInit mInit;
	mInit.r = 255;
	mInit.g = 255;
	mInit.b = 255;
	mInit.numFrames = 4;
	mInit.pause = 90;
	
	for (int i = 0; i<MAX_PLAYERS; i++)
	{
		mInit.bmpFile = spriteFiles[i].filename;
		TankSpriteBase[i].init(&mInit);
	}
}

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
	
	LoadTankSprites();
	
	for (int i = 0; i<MAX_PLAYERS; i++)
	{
		players[i].init(&TankSpriteBase[i],game_video->get_screen());
		players[i].set(25+i*40,400);
		players[i].setSpeed(0.9);
		players[i].setID(i);
		players[i].setHP(100);
		players[i].toggleAnim();
	}
	
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
	
	for (int i = 0; i<MAX_PLAYERS; i++)
	{
		players[i].clearBG();
		players[i].updateBG();
		players[i].draw();
	}
	
	game_video->SwapScreen();
}

void gameCore::NetStart(void)
{
	game_network->Start();
}

void gameCore::playerInput(void)
{
	// input listener
	
	int speed = players[selfID].getSpeed();
	
	players[selfID].stopAnim();
	
	if (game_keys[SDLK_LEFT])
	{
		players[selfID].startAnim();
		players[selfID].setOrientation(TANK_LEFT);
		players[selfID].xadd(-speed);
	}
	
	if (game_keys[SDLK_RIGHT])
	{
		players[selfID].startAnim();
		players[selfID].setOrientation(TANK_RIGHT);
		players[selfID].xadd(speed);
	}
	
	if (game_keys[SDLK_UP])
	{
		players[selfID].startAnim();
		players[selfID].setOrientation(TANK_UP);
		players[selfID].yadd(-speed);
	}
	
	if (game_keys[SDLK_DOWN])
	{
		players[selfID].startAnim();
		players[selfID].setOrientation(TANK_DOWN);
		players[selfID].yadd(speed);
	}
	
}
