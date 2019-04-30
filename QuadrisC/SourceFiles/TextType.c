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
#include "TextType.h"

/***  ANSI C Header Files  ***/
#include <stdio.h>

/***  Custom Header Files  ***/
#include "Globals.h"

TTF_Font* p_font = NULL;

const Bool InitTextType( void )
{
	Bool rtn = False;

	if (TTF_Init() < 0)
		fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
	else {
		fprintf(stderr, "TTF Initialized.\n");
		rtn = True;
	}

	return rtn;
}

void LoadTextTypes( void )
{
	LoadTextType(&p_font, "Resource/FreeSansBold.ttf");
}

void LoadTextType( TTF_Font** font, const char* filename )
{
	int size = 16;
	if (filename != "") {
		if ((*font = TTF_OpenFont(filename, size)) == NULL)
			fprintf(stderr, "Unable to load %s TTF file.\n%s\n", filename, TTF_GetError());
	}
}

SDL_Surface* RenderText( const char* text )
{
	SDL_Colour colour = {255, 255, 255};
	SDL_Surface* rtn = NULL;
	
	if ((rtn = TTF_RenderText_Solid(p_font, text, colour) ) == NULL)
		fprintf(stderr, "Unable to Render Text.\n%s\n", TTF_GetError());

	return rtn;
}

void DeleteTextTypes( void )
{
	DeleteTextType(&p_font);
}

void DeleteTextType( TTF_Font** font )
{
	if (*font != NULL)
	{
		TTF_CloseFont(*font);
		*font = NULL;
	}
}