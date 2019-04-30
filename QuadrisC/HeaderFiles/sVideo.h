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
#ifndef _SVIDEO_H_
#define _SVIDEO_H_

/***  SDL Header Files  ***/
#include <SDL.h>

typedef struct sVideo
{
	const unsigned long int WIDTH;
	const unsigned long int HEIGHT;
	const unsigned long int BIT;
	const unsigned long int FLAGS;

	const char* TITLE;

	SDL_Surface* Display;
} sVideo;

#endif/// END IFNDEF _SVIDEO_H_