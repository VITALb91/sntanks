#ifndef __gameCore_H__
#define __gameCore_H__

#include "SDL.h"
#include "videoCore.h"
#include "coreNetwork.h"

const int FPS = 30;
const int FrameDuration = 1000 / FPS;
const int MaxFrameSkip = 10;

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
	bool Init(int width, int height, int bpp);
	void Start(void);
	void RenderScene(void);
};

#endif
