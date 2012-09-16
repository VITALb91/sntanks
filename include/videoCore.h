#ifndef __videoCore_H__
#define __videoCore_H__

#include "SDL.h"
#include <stdio.h>

class videoCore
{
	private:
	SDL_Surface *user_screen;
	
	public:
	videoCore(void);
	~videoCore(void);
	bool CreateWindow(int width, int height, int bpp, const char *app_title, const char *icon_path, bool fullscreen);
	void SwapScreen(void);
	void DrawPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
	void ScreenLock();
	void ScreenUnlock();
	int get_width();
	int get_height();
	SDL_Surface* get_screen();
};

#endif
