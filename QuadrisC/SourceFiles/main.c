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
/***  ANSI C Header Files  ***/
#include <stdio.h>	// for fprintf() call
#include <stdlib.h>	// for atexit() and exit() call

/***  SDL Header Files  ***/
#include <SDL.h>

/***  Custom Header Files  ***/
#include "Game.h"

int main( int argc, char *argv[] )
{
	atexit(DoneGame);
	
	//if program initialization failed, then return with 0
	if(!InitGame()) {
		fprintf(stderr, "Game Init failed!\n");
		exit(1);
	}
	else
		LoopGame();

	return 0;
}