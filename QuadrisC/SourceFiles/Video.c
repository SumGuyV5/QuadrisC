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
#include "Video.h"

/***  ANSI C Header Files  ***/
#include <stdio.h>	// for fprintf() call

/***  Custom Header Files  ***/
#include "eMap.h"
#include "eTile.h"
#include "sVideo.h"
#include "Score.h"
#include "Globals.h"


sVideo gVideo = {280, 480, 16, SDL_HWSURFACE | SDL_DOUBLEBUF, "Quadris C", NULL};
SDL_Surface* gsurfBlocks = NULL;

const Bool InitVideo( void )
{
	Bool rtn = True;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		rtn = False;
	}
	else
		fprintf(stderr, "SDL Initialized.\n");

	gVideo.Display = SDL_SetVideoMode(gVideo.WIDTH, gVideo.HEIGHT, gVideo.BIT, gVideo.FLAGS);	
	
	if (!gVideo.Display) {
		fprintf(stderr, "Cannot set Video Mode: %s\n", SDL_GetError());
		rtn = False;    
	}
	else
		fprintf(stderr, "Video Mode Initialized.\n");


	SDL_WM_SetCaption(gVideo.TITLE, gVideo.TITLE);

	return rtn;
}

void LoadSurfaces( void )
{
	LoadSurface(&gsurfBlocks, "Resource/blocks.bmp");
}

void LoadSurface( SDL_Surface** surface, const char* filename )
{
	if (*surface == NULL)
		*surface = SDL_LoadBMP(filename);

	if (*surface == NULL)
		fprintf(stderr, "File not Found: %s\n", filename);
}

void DeleteSurfaces( void )
{
	DeleteSurface(&gsurfBlocks);
}

void DeleteSurface( SDL_Surface** surface)
{
	if (*surface != NULL)
	{
		SDL_FreeSurface(*surface);
		*surface = NULL;
	}
}

void MapDraw( void ) 
{
	unsigned long int x = 0, y = 0;	//place the toolbar
	SDL_Rect DestR = {MAPWIDTH * TILESIZE, 400, 0, 0};

	//draw gray area
	for(x = MAPWIDTH; x < MAPWIDTH + MAPGREY; ++x)
		for(y = 0 ; y < MAPHEIGHT; ++y)
			TileDraw(x, y, GREY);

	//draw preview block
	for(x = 0; x < 4; ++x)
		for(y = 0; y < 4; ++y)
			if(gNextPiece.size[x][y] != NODRAW)
				TileDraw(gNextPiece.x + x, gNextPiece.y + y, gNextPiece.size[x][y]);
	
	//draw the map	//loop through the positions
	for(x = 0; x < MAPWIDTH; ++x)
		for(y = 0; y < MAPHEIGHT; ++y)
				TileDraw(x, y, gMap[x][y]);	

	//draw moving block
	for(x = 0; x < 4; ++x)
		for(y = 0; y < 4; ++y)
			if(gPiece.size[x][y] != NODRAW)
				TileDraw(gPiece.x + x, gPiece.y + y, gPiece.size[x][y]);	//Redraw the entire Display
	
	SDL_BlitSurface(GetSrufScore(), NULL, gVideo.Display, &DestR);

	SDL_Flip(gVideo.Display);
}

void TileDraw( const unsigned long int x, const unsigned long int y, const unsigned long int tile ) 
{
	Blit(gVideo.Display, x*TILESIZE, y*TILESIZE, gsurfBlocks, tile*TILESIZE, 0, TILESIZE, TILESIZE);
}

void Blit( SDL_Surface *Dest, const unsigned long int DestX, const unsigned long int DestY, SDL_Surface *Src, const unsigned long int SrcX, const unsigned long int SrcY, const unsigned long int SrcW,  const unsigned long int SrcH )
{
	//Create a 2 Rects. The first is for where we want to Blit to.
	//The other is for clipping the 'Src' so we only draw the portion we want
	SDL_Rect DestR = {DestX, DestY, 0, 0};
	SDL_Rect SrcR = {SrcX, SrcY, SrcW, SrcH};

	SDL_BlitSurface(Src, &SrcR, Dest, &DestR);
}