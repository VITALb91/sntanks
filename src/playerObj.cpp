#include "../include/playerObj.h"

playerObj::playerObj()
{
	ID = selfID;
	speedPPX = 1;
	health = 100;
	sDrawn = 0;
	sFrame = 0;
	Orientation = TANK_RIGHT;
	sLastupdate = 0;
}

int spriteBase::init(spriteInit* data)
{
	int r, g, b;
	r = data->r;
	g = data->g;
	b = data->b;
      
	sPause = data->pause;
	sNumFrames = data->numFrames;
  
	SDL_Surface *temp;
	if ((temp = SDL_LoadBMP(data->bmpFile))==NULL) return -1;
  
	sW = temp->w/sNumFrames;
	sH = temp->h/sNumFrames;
  
	SDL_Rect srcr;
	srcr.x = 0;
	srcr.y = 0;  
	srcr.w = sW;
	srcr.h = sH;
  

	SDL_Surface *temp1;
	Uint32 rmask, gmask, bmask, amask;
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif
	temp1 = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCCOLORKEY, sW, sH, 32, rmask, gmask, bmask, amask);
	
	if(temp1 == NULL) 
	{
		printf("CreateRGBSurface temp1 failed: %s\n", SDL_GetError());
		return -1;
	}
  
	for(int j = 0; j<sNumFrames; j++)
	{
		for (int i = 0; i<sNumFrames; i++)
		{
			srcr.x = i*sW;
			srcr.y = j*sH;
			SDL_BlitSurface(temp,&srcr,temp1,NULL);

			if(r>=0 && g>=0 && b>=0)
			  SDL_SetColorKey(temp1,SDL_SRCCOLORKEY,SDL_MapRGB(temp1->format,r,g,b));
			
			sAnim[j][i].image = SDL_DisplayFormat(temp1);
		}
	}
  
	SDL_FreeSurface(temp1);
	SDL_FreeSurface(temp);
	return 0;
}



int playerObj::init(spriteBase *base, SDL_Surface *screen)
{
	sSpriteBase = base;
	sAnimating = (sSpriteBase->sNumFrames>1)? 1 : 0;
    sBackreplacement = SDL_DisplayFormat(sSpriteBase->sAnim[0][0].image);
	sScreen = screen;
	return 0;
}

void playerObj::clearBG()
{
	if(sDrawn==1)
	{
		SDL_Rect dest;
		dest.x = sOldX;
		dest.y = sOldY;
		dest.w = sSpriteBase->sW;
		dest.h = sSpriteBase->sH;
		SDL_BlitSurface(sBackreplacement, NULL, sScreen, &dest);
	}
}

void playerObj::updateBG()
{
	SDL_Rect srcrect;
	srcrect.w = sSpriteBase->sW;
	srcrect.h = sSpriteBase->sH;
	srcrect.x = sX;
	srcrect.y = sY;
	sOldX = sX;
	sOldY = sY;
	SDL_BlitSurface(sScreen, &srcrect, sBackreplacement, NULL);
}

void playerObj::draw()
{
	if(sAnimating)
	{
		if(sLastupdate+sSpriteBase->sPause*sSpeed < SDL_GetTicks())
		{
			sFrame++;
			if(sFrame>sSpriteBase->sNumFrames-1) sFrame = 0;
			sLastupdate = SDL_GetTicks();
		}
	}

	if(sDrawn == 0) sDrawn = 1;

	SDL_Rect dest;
	dest.x = sX; dest.y = sY;
	SDL_BlitSurface(sSpriteBase->sAnim[Orientation][sFrame].image, NULL, sScreen, &dest);
}
