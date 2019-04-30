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
#ifndef _VIDEO_H_
#define _VIDEO_H_

/***  SDL Header Files  ***/
#include <SDL.h>

/***  Custom Header Files  ***/
#include "eBool.h"

const Bool InitVideo( void );

void LoadSurfaces( void );
void LoadSurface( SDL_Surface** surface, const char* filename );

void DeleteSurfaces( void );
void DeleteSurface( SDL_Surface** surface);

void MapDraw( void ); //draw the whole map.. render function, basically
void TileDraw( const unsigned long int x, const unsigned long int y, const unsigned long int tile); //coordinates & tile type
void Blit( SDL_Surface *Dest, const unsigned long int DestX, const unsigned long int DestY, SDL_Surface *Src, const unsigned long int SrcX, const unsigned long int SrcY, const unsigned long int SrcW, const unsigned long int SrcH );

#endif/// END IFNDEF _VIDEO_H_