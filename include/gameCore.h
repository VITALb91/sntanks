#ifndef __gameCore_H__
#define __gameCore_H__

#define __DEBUG_MODE__

#include "SDL.h"
#include "SDL_thread.h"
#include "SDL_mutex.h"
#include "videoCore.h"
#include "coreNetwork.h"

const int FPS = 30;
const int FrameDuration = 1000 / FPS;
const int MaxFrameSkip = 10;

int StartNetwork_thread(void *data);

class gameCore
{
	private:
	Uint8* game_keys;
	SDL_Event game_event;
	videoCore *game_video;
	coreNetwork *game_network;
	
	public:
	gameCore(void);
	~gameCore(void);
	bool Init(int width, int height, int bpp, char *hostname, int port);
	void Start(void);
	void RenderScene(void);
	void NetStart(void);
	void playerInput(void);
};

#endif
