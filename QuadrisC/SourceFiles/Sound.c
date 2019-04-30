/*	Copyright (C) 2011 Richard W. Allen
	Program Name:  Quadris C
	Author:        Richard W. Allen
	Version:       V1.1
	Date Started:  January 24, 2011
	Date End:	   March 02, 2011
	Updated:	   December 15, 2011
	Webpage:       http://www.richardallenonline.com
	IDE:           Visual Studio 2010 (Windows 7), Code::Blocks 10.05 (Ubuntu 10.04 LTS)
	Compiler:      C\C++ 2010 (Windows 7), gcc 4.4.3 (Ubuntu 10.04 LTS), devkitPPC 1.5.0 (Wii)
	Langage:       C
	License:       GNU GENERAL PUBLIC LICENSE Version 2
				   see license.txt for details

	Quadris C Copyright (C) 2011 Richard W. Allen 
	Comes with ABSOLUTELY NO WARRANTY;
	Quadris C is licensed under the GNU GENERAL PUBLIC LICENSE Version 2.
	for details see the license.txt include with this program.
*/
#include "Sound.h"

/***  ANSI C Header Files  ***/
#include <stdio.h>	// for fprintf() call

Mix_Chunk* p_stopSound = NULL;
Mix_Chunk* p_rotateSound = NULL;
Mix_Chunk* p_removeRowSound = NULL;

long int channel = -1, volume = 255, angle = 0, distance = 100, loops = 0;

const Bool InitSound( void )
{
	Bool rtn = False;

	if(SDL_InitSubSystem(SDL_INIT_AUDIO) != 0)
		fprintf(stderr, "Could not initialize SDL_AUDIO: %s\n", SDL_GetError());
	else {
		fprintf(stderr, "Audio Initialized.\n");
		rtn = True;
	}

	if (Mix_OpenAudio(22050, AUDIO_S16, 2, 0) < 0)
		fprintf(stderr, "Error initializing SDL_mixer: %s\n", Mix_GetError());

	Mix_Volume(channel, volume);
	if (Mix_SetPosition(channel, angle, distance) == -1)
		fprintf(stderr, "Mix_SetPosition: %s\n", Mix_GetError());

	return rtn;
}

void LoadSounds( void )
{
	LoadSound(&p_stopSound, "Resource/stop.wav");
	LoadSound(&p_rotateSound, "Resource/rotate.wav");
	LoadSound(&p_removeRowSound, "Resource/lineremove.wav");

}

void LoadSound( Mix_Chunk** sound, const char* filename )
{
	if(*sound == NULL)
		*sound = Mix_LoadWAV(filename);

	if(*sound == NULL)
		fprintf(stderr, "Could not Load '%s'.\n", filename);
}

void DeleteSounds( void )
{
	DeleteSound(&p_stopSound);
	DeleteSound(&p_rotateSound);
	DeleteSound(&p_removeRowSound);
	
	Mix_CloseAudio();
}

void DeleteSound( Mix_Chunk** sound )
{
	if (*sound != NULL)
	{
		Mix_FreeChunk(*sound);
		*sound = NULL;
	}
}

void RotateSound( void )
{
	PlaySound(p_rotateSound);
}

void StopSound( void )
{
	PlaySound(p_stopSound);
}

void RemoveRowSound( void )
{
	PlaySound(p_removeRowSound);
}

void PlaySound( Mix_Chunk* sound )
{
	if (sound != NULL) {
		if (Mix_PlayChannel(channel, sound, loops) == -1)
			fprintf(stderr, "Mix_PlayChannel: %s\n", Mix_GetError());
	}
}