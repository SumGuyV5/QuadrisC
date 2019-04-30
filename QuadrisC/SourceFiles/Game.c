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
#include "Game.h"

/***  SDL Header Files  ***/
#include <SDL.h>	// for SDL_Event SDL_Quit()

/***  ANSI C Header Files  ***/
#include <time.h>	// for time() call in InitGame()
#include <stdio.h>	// for fprintf() call in InitGame()
#include <stdlib.h>	// for srand() call in InitGame()

/***  Custom Header Files  ***/
#include "eTile.h"		// for Tile Colouring GRAY and BLACK in NewGame()
#include "Sound.h"		// for InitSound() and LoadSounds() calls in InitGame(); DeleteSounds() call in DoneGame()
#include "Timer.h"		// for InitTimer() and setFTP() calls in InitGame(); Time() and Timer() call in LoopGame()
#include "TextType.h"	// for InitTextType() and LoadTextTypes() call in InitGame(); DeleteTextTypes() in DoneGame()
#include "Video.h"		// for InitVideo() and LoadSurfaces() calls in InitGame(); MapDraw() call in LoopGame()
#include "Block.h"		// for NewBlock() call in NewGame(); DownBlock() call in LoopGame(); MoveBlock() call in EventGame()
#include "Score.h"		// for ClearScore() call in NewGame() 
#include "Globals.h"	// for gMap
#include "JoyStick.h"	// for InitJoyStick() calls in InitGame(); CloseJoyStick() call in DoneGame()

unsigned long int fallSpeed = 1000;

const Bool InitGame( void )
{
	Bool rtn = True;

	if (InitVideo() == False)
		fprintf(stderr, "Video Setup Failed.\n");
	else
		LoadSurfaces();

	if(InitSound() == False)
		fprintf(stderr, "Sound Setup Failed.\n");
	else
		LoadSounds();

	if(InitTimer() == False)
		fprintf(stderr, "Timer Setup Failed.\n");

	if(InitTextType() == False)
		fprintf(stderr, "TTF Setup Failed.\n");
	else
		LoadTextTypes();

	if(InitJoyStick() == False)
		fprintf(stderr, "JoyStick Setup Failed.\n");

	srand((unsigned int)time(NULL));
	setFTP(30);

	NewGame();

	return rtn;
}

void NewGame( void ) 
{
	unsigned long int x = 0, y = 0;
	ClearScore();
	for(x = 0; x < MAPWIDTH; ++x) {
		for(y = 0; y < MAPHEIGHT + 1; ++y) {
			if(y == MAPHEIGHT) //makes Y-collision easier.
				gMap[x][y] = GREY;
			else
				gMap[x][y] = BLACK;
		}
	}
	NewBlock( True );
}

void DoneGame( void ) 
{
	DeleteSurfaces();
	DeleteSounds();
	DeleteTextTypes();
	CloseJoyStick();
	SDL_Quit();
}

void LoopGame( void ) 
{
	//Main game loop
	while(!EventGame()) {
		MapDraw();
		Time();
		Timer(fallSpeed, DownBlock);
	}
}

const Bool EventGame( void )
{
	Bool rtn = False;
	SDL_Event Event;
	while (SDL_PollEvent(&Event)) {		
		switch (Event.type) 
		{
			case SDL_QUIT:		//Found a quit event				
				rtn = True;				
				break;			
			case SDL_KEYDOWN:	//A key has been pressed				
				switch(Event.key.keysym.sym) 
				{					
					case SDLK_ESCAPE:						
						rtn = True;						
						break;					
					case SDLK_DOWN:
						fallSpeed = 50;
						break;
					case SDLK_UP:
						RotateBlock();
						break;
					case SDLK_LEFT:
						MoveBlock(-1, 0);
						break;
					case SDLK_RIGHT:
						MoveBlock(1, 0);
						break;
				}
				break;
			case SDL_KEYUP:
				switch(Event.key.keysym.sym) 
				{					
					case SDLK_DOWN:						
						fallSpeed = 1000;						
						break;
				}
				break;
			case SDL_JOYHATMOTION:
				switch(Event.jhat.value)
				{
					case SDL_HAT_UP:
						RotateBlock();
						break;
					case SDL_HAT_DOWN:
						fallSpeed = 250;
						break;
					case SDL_HAT_LEFT:
						MoveBlock(-1, 0);
						break;
					case SDL_HAT_RIGHT:
						MoveBlock(1, 0);
						break;
					default:
						fallSpeed = 1000;
						break;
				}
				break;
			case SDL_JOYBUTTONDOWN:
				switch(Event.jbutton.button)
				{
					case 6:
						rtn = True;
						break;
				}
				break;
		}
	}
	return rtn;
}