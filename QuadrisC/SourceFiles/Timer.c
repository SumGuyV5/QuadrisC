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
#include  "Timer.h"

/***  ANSI C Header Files  ***/
#include <stdio.h>	// for fprintf() call

unsigned long int nextTime = 0;
unsigned long int rate = 0;
unsigned long int FPS = 0;
unsigned long int start = 0;

const Bool InitTimer( void )
{
	Bool rtn = False;

	if(  SDL_Init( SDL_INIT_TIMER ) != 0  ) 
		fprintf(stderr, "Could not initialize SDL_TIMER: %s\n", SDL_GetError());
	else {
		fprintf(stderr, "Timer Initialized.\n");
		rtn = True;
	}

	TimerSetup();

	return rtn;
}

void TimerSetup( void )
{
	nextTime = SDL_GetTicks();
	AddTimeandRate();
}

void Time( void )
{
	SDL_Delay(TimeLeft());
	AddTimeandRate();
}

void Timer( const unsigned long int wait, void (*func)() )
{
	static unsigned long int lastTime = 0;
	if((SDL_GetTicks() - lastTime) > wait) {
		func();
		lastTime = SDL_GetTicks();
	}
}

void setFTP( const unsigned long int fps /*= 30*/ )
{
	FPS = fps;
	rate = 1000 / FPS;
	TimerSetup();
}

void AddTimeandRate()
{
	nextTime += rate;
}

const unsigned long int TimeLeft( void )
{
	unsigned long int now = SDL_GetTicks();

	if(nextTime <= now)
		return 0;
	else
		return nextTime - now;
}