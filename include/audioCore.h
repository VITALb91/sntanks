#ifndef __audioCore_H__
#define __audioCore_H__

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>

#define SND_CHANNEL_ALL -1

enum audioChunksID { SND_shoot, SND_move, SND_explosion };

struct WavFile
{
	char *filename;
};

struct SimpleChunk
{
	Mix_Chunk *chunk;
};

class audioCore
{
	private:
	SimpleChunk *sound;
	void LoadWaves();
	
	public:
	audioCore() {}
	~audioCore();
	bool Init(int volume);
	void PlaySound(int ID, int channel,int time_length);
	void PauseSound(int channel) { Mix_Pause(channel); }
	void ResumeSound(int channel) { Mix_Resume(channel); }
	void StopSound(int channel) { Mix_HaltChannel(channel); }
	void setVolume(int channel, int volume) { Mix_Volume(channel, volume); }
	int getVolume(int channel) { return Mix_Volume(channel, -1); }
};

#endif
