#include "../include/videoCore.h"

videoCore::videoCore()
{
}

videoCore::~videoCore()
{
}

bool videoCore::CreateWindow(int width, int height, int bpp, const char *app_title, const char *icon_path, bool fullscreen)
{
	Uint32 flags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	flags |= fullscreen? SDL_FULLSCREEN : 0;
	
	SDL_WM_SetCaption(app_title,NULL);
	if (icon_path!=NULL)
		SDL_WM_SetIcon(SDL_LoadBMP(icon_path), NULL);
	
	user_screen = SDL_SetVideoMode(width,height,bpp,flags);
	if ( user_screen == NULL )
	{ 
		printf("Unable to set %dx%d video: %s\n", width, height, SDL_GetError()); 
		return false;
	}
	
	return true;
}

void videoCore::SwapScreen()
{
	SDL_Flip(user_screen);
}

void videoCore::DrawPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{ 
	/*
		Sample function for drawing different pixels (now useless, just in case)
		as is from
		http://www.libsdl.org/
	*/

	Uint32 color = SDL_MapRGB(user_screen->format, R, G, B); 
	switch (user_screen->format->BytesPerPixel)
	{ 
		case 1:  // Assuming 8-bpp 
		{ 
			Uint8 *bufp; 
			bufp = (Uint8 *)user_screen->pixels + y*user_screen->pitch + x; *bufp = color; 
		} 
		break;
		 
		case 2: // Probably 15-bpp or 16-bpp 
		{ 
			Uint16 *bufp; 
			bufp = (Uint16 *)user_screen->pixels + y*user_screen->pitch/2 + x; *bufp = color; 
		} 
		break;
		 
		case 3: // Slow 24-bpp mode, usually not used 
		{ 
			Uint8 *bufp; 
			bufp = (Uint8 *)user_screen->pixels + y*user_screen->pitch + x * 3; 
			if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
			{ 
				bufp[0] = color; 
				bufp[1] = color >> 8; 
				bufp[2] = color >> 16; 
			}
			else
			{ 
				bufp[2] = color; 
				bufp[1] = color >> 8; 
				bufp[0] = color >> 16; 
			} 
		}
		break;
		 
		case 4: // Probably 32-bpp 
		{ 
			Uint32 *bufp; 
			bufp = (Uint32 *)user_screen->pixels + y*user_screen->pitch/4 + x; 
			*bufp = color; 
		} 
		break; 
	} 

} 

void videoCore::ScreenLock()
{ 
	if ( SDL_MUSTLOCK(user_screen) )
		if ( SDL_LockSurface(user_screen) < 0 )
			return;
} 


void videoCore::ScreenUnlock()
{
	if ( SDL_MUSTLOCK(user_screen) )
		SDL_UnlockSurface(user_screen); 
} 

int videoCore::get_width()
{
	return (user_screen->w);
}

int videoCore::get_height()
{
	return (user_screen->h);
}

SDL_Surface* videoCore::get_screen()
{
	return user_screen;
}
