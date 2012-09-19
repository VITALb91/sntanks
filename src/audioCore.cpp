#include "../include/audioCore.h"

WavFile audioPath[] = 
{ 
	"data/sound/TankShoot.wav",
	"data/sound/TankMove.wav",
	"data/sound/Explosion.wav"
};

audioCore::~audioCore()
{
	delete sound;
	sound = NULL;
	Mix_CloseAudio();
}

void audioCore::LoadWaves()
{
	int sndCount = sizeof(audioPath)/sizeof(WavFile);
	sound = new SimpleChunk[sndCount];
	
	for (int i = 0; i<sndCount; i++)
		sound[i].chunk = Mix_LoadWAV(audioPath[i].filename);
}

bool audioCore::Init(int volume)
{
	if (Mix_OpenAudio(16000, AUDIO_S16SYS, 2, 4096) < 0) 
	{
		printf("Audio mixer init error\n");
		return false;	
	}
	
	LoadWaves();
	
	setVolume(SND_CHANNEL_ALL, volume);
	
	return true;
}

void audioCore::PlaySound(int ID, int channel, int time_length)
{
	if (!Mix_Playing(channel))
	{
		if (!Mix_Paused(channel))
			Mix_PlayChannelTimed(channel, sound[ID].chunk, 0, time_length);
		else
			ResumeSound(channel);
	}
}
