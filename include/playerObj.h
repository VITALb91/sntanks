#ifndef __playerObj_H__
#define __playerObj_H__

/*
	Modified sprite system to the game.
	Original:
	http://plg.lrn.ru/
	bbroth@pochta.ru
*/

#include <stdio.h>
#include "SDL.h"

const int selfID = 0;
const int MAX_PLAYERS = 4;

enum Tank_Orientation { TANK_RIGHT = 0, TANK_LEFT, TANK_UP, TANK_DOWN };

struct spriteInit
{
	char* bmpFile;
	int numFrames;
	int pause;
	int r;
	int g;
	int b;
};

struct spriteFrame
{
	SDL_Surface* image;
};

class spriteBase
{
	public:
	int init(spriteInit* data);
  
	spriteFrame sAnim[4][4];
	int sPause;
	int sNumFrames;
	int sW, sH;
};

class playerObj
{
	private:
	int ID;
	int health;
	int speedPPX;
	
	int Orientation;
	int sFrame;
	int sX, sY, sOldX, sOldY;
	int sAnimating;
	int sDrawn;
	float sSpeed;
	long sLastupdate;
	spriteBase *sSpriteBase;
	SDL_Surface *sBackreplacement;
	SDL_Surface *sScreen;
	
	public:
	
	playerObj();
	~playerObj() {}
	
	
	int init(spriteBase *base, SDL_Surface *screen);
	void draw();
	void clearBG();
	void updateBG();
	void setFrame(int nr) { sFrame = nr; }
	int getFrame() { return sFrame; }
	void setSpeed(float nr) { sSpeed = nr; }
  
	void toggleAnim() { sAnimating = !sAnimating; }
	void startAnim() { sAnimating = 1; }
	void stopAnim() {sAnimating = 0; }
  
	void xadd(int nr) { sX+=nr; }
	void yadd(int nr) { sY+=nr; }  
	void xset(int nr) { sX=nr; }
	void yset(int nr) { sY=nr; }
	void set(int xx, int yy) { sX=xx; sY=yy; }
	void setOrientation(int Orient) { Orientation = Orient; }
	
	void setID(int id) { ID = id; }
	int getID() { return ID; }
	void setHP(int hp) { health = hp; } 
	int getSpeed() { return speedPPX; }
};

#endif
