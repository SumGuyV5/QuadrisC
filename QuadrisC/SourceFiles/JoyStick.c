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
#include "JoyStick.h"

/***  SDL Header Files  ***/
#include <SDL.h>	// for SDL_Event SDL_Quit()

SDL_Joystick* joy = NULL;

const Bool InitJoyStick( void )
{
	Bool rtn = False;

	if(SDL_InitSubSystem(SDL_INIT_JOYSTICK) != 0)
		fprintf(stderr, "Could not initialize SDL_JOYSTICK: %s\n", SDL_GetError());
	else {
		fprintf(stderr, "JoyStick Initialized.\n");
		rtn = True;
	}

	if(SDL_NumJoysticks() > 0){
		// Open joystick
		joy = SDL_JoystickOpen(0);

		if(joy)
		{
			fprintf(stderr, "Opened Joystick 0\n");
			fprintf(stderr, "Name: %s\n", SDL_JoystickName(0));
			fprintf(stderr, "Number of Axes: %d\n", SDL_JoystickNumAxes(joy));
			fprintf(stderr, "Number of Buttons: %d\n", SDL_JoystickNumButtons(joy));
			fprintf(stderr, "Number of Balls: %d\n", SDL_JoystickNumBalls(joy));
		}
		else
			fprintf(stderr, "Couldn't open Joystick 0\n");		
	}

	return rtn;
}

void CloseJoyStick( void )
{
	// Close if opened
	if(SDL_JoystickOpened(0))
		SDL_JoystickClose(joy);
}