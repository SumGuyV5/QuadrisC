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
#include "Score.h"

/***  ANSI C Header Files  ***/
#include <stdio.h>	// for sprintf() call
#include <string.h> // for strcat() call

/***  Custom Header Files  ***/
#include "TextType.h"
#include "sScoreBoard.h"

sScoreBoard scoreBoard = {NULL, 0};

void ClearScore( void )
{
	scoreBoard.score = 0;

	LineScore(0);
}

void ClearSurface( void )
{
	if (scoreBoard.surfBoard == NULL) {
		SDL_FreeSurface(scoreBoard.surfBoard);
		scoreBoard.surfBoard = NULL;
	}
}

void LineScore( const unsigned long int mul )
{
	char text[20] = "Score: ";
	char buffer[10];
	scoreBoard.score += 1000 * mul;

	ClearSurface();

	if (scoreBoard.score < 100000000000) // to stop from going over the buffer
		sprintf(buffer, "%d", (int)scoreBoard.score);

	strcat( text, buffer );
	scoreBoard.surfBoard = RenderText(text);
}

SDL_Surface* GetSrufScore( void )
{
	return scoreBoard.surfBoard;
}
