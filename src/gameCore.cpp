#include "../include/gameCore.h"

gameCore::gameCore()
{
	game_video = NULL;
}

gameCore::~gameCore()
{
	SDL_Quit();
	delete game_video;
	game_video = NULL;
}

bool gameCore::Init(int width = 800, int height = 600, int bpp = 32)
{
	if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
	{ 
		printf("Unable to init SDL: %s\n", SDL_GetError()); 
		return false;
	}
	
	game_video = new videoCore();
	
	if ( !game_video || !game_video->CreateWindow(width,height,bpp,"Tanks",NULL,false) ) return false;
}


void gameCore::Start()
{
	int loops = 0;
	int done = 0;
	
	long nextFrameTime = SDL_GetTicks();
	
	while(done == 0)
	{  
   
		while ( SDL_PollEvent(&game_event) )
		{ 
			if ( game_event.type == SDL_QUIT ) done = 1; 
			if ( game_event.type == SDL_KEYDOWN )
				if ( game_event.key.keysym.sym == SDLK_ESCAPE ) done = 1; 
		}
	   
		game_keys = SDL_GetKeyState(NULL);
		
		while( SDL_GetTicks() > nextFrameTime && loops < MaxFrameSkip )
		{
			/*
				player input listener here
			*/
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
