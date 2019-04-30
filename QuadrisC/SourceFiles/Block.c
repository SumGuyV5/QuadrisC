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
#include "Block.h"

/***  Custom Header Files  ***/
#include "eTile.h"			// for Tile Colouring in NewBlock(), RotateBlock(), GenBlock()
#include "eBool.h"
#include "Sound.h"
#include "Score.h"
#include "Game.h"
#include "Globals.h"

void NewBlock( const Bool start ) 
{
	ClearPiece(&gPiece);

	gPiece.x = (MAPWIDTH / 2) - 2;
	gPiece.y = -1;

	if(start == True)
		GenBlock(&gPiece);
	else
		CopyPiece(&gPiece, &gNextPiece);

	ClearPiece(&gNextPiece);

	//Position the next piece into the grey area to the right.
	gNextPiece.x = MAPWIDTH + (MAPGREY / 4);
	gNextPiece.y = MAPGREY / 4;

	GenBlock(&gNextPiece);
}

void DownBlock( void )
{
	MoveBlock(0,1);
}

void MoveBlock( const long int nx, const long int ny ) 
{
	if(CollisionTest(nx, ny)) {
		if(ny == 1) {
			if(gPiece.y < 1) {
				NewGame(); //you lose!  new game.
			} else {
				unsigned long int x = 0, y = 0, count = 0;		
				StopSound();
				//new block time! add this one to the list!
				for(x = 0; x < 4; ++x)
					for(y = 0; y < 4; ++y)
						if(gPiece.size[x][y] != NODRAW)
							gMap[gPiece.x + x][gPiece.y + y] = gPiece.size[x][y];

				//check for cleared row!
				for(y = 0, count = 0; y < MAPHEIGHT; ++y) {
					Bool filled = True;
					for(x = 0; x < MAPWIDTH; ++x)
						if(gMap[x][y] == BLACK)
							filled = False;
					if(filled == True) {
						RemoveRow(y);
						ClearPiece(&gPiece);
						++count;
					}
				}
				if (count != 0) {
					LineScore(count);
					RemoveRowSound();
				}

				NewBlock( False );
			}
		}
	}else{
		gPiece.x += nx;
		gPiece.y += ny;
	}
}

void RotateBlock( void ) 
{
	//copy & rotate the piece to the temporary array
	long int x = 0, y = 0;
	sPiece temp;

	for(x = 0; x < 4; ++x)
		for(y = 0; y < 4; ++y)
			temp.size[3 - y][x] = gPiece.size[x][y];	
	
	//check collision of the temporary array with map borders
	for(x = 0; x < 4; ++x)
		for(y = 0; y < 4; ++y)
			if(temp.size[x][y] != NODRAW)
				if((gPiece.x + x < 0) || (gPiece.x + x > MAPWIDTH - 1) || (gPiece.y + y < 0) || (gPiece.y + y > MAPHEIGHT - 1))
					return;	
	
	//check collision of the temporary array with the blocks on the map
	for(x = 0; x < MAPWIDTH; ++x)
		for(y = 0; y < MAPHEIGHT; ++y)
			if((x >= gPiece.x) && (x < gPiece.x + 4))
				if((y >= gPiece.y) && (y < gPiece.y + 4))
					if(gMap[x][y] != BLACK)
						if(temp.size[x - gPiece.x][y - gPiece.y] != NODRAW)
							return;	
	
	//end collision check	
	
	//successful!  copy the rotated temporary array to the original piece
	CopyPiece(&gPiece, &temp);
	RotateSound();
}

void GenBlock( sPiece* const piece )
{
	//  0   1   2   3   4    5   6
	//   X                             These
	//   X   XX   X  XX   XX  XX   XX  are
	//   X   XX  XXX  XX XX    X   X   block
	//   X                     X   X   types
	//begin game! make generate a block and then one in preview.
	switch (rand() % 7)
	{
	case 0: //Line
		piece->size[1][0] = RED;
		piece->size[1][1] = RED;
		piece->size[1][2] = RED;
		piece->size[1][3] = RED;
		piece->y = 0;
		break;
	case 1: //Box!
		piece->size[1][1] = BLUE;
		piece->size[1][2] = BLUE;
		piece->size[2][1] = BLUE;
		piece->size[2][2] = BLUE;
		break;
	case 2: //Pyramid!
		piece->size[1][1] = STEEL;
		piece->size[0][2] = STEEL;
		piece->size[1][2] = STEEL;
		piece->size[2][2] = STEEL;
		break;
	case 3://Left Leaner
		piece->size[0][1] = YELLOW;
		piece->size[1][1] = YELLOW;
		piece->size[1][2] = YELLOW;
		piece->size[2][2] = YELLOW;
		break;
	case 4://Right Leaner
		piece->size[2][1] = GREEN;
		piece->size[1][1] = GREEN;
		piece->size[1][2] = GREEN;
		piece->size[0][2] = GREEN;
		break;
	case 5://Z
		piece->size[1][1] = WHITE;
		piece->size[2][1] = WHITE;
		piece->size[2][2] = WHITE;
		piece->size[2][3] = WHITE;
		break;
	case 6://S
		piece->size[2][1] = PURPLE;
		piece->size[1][1] = PURPLE;
		piece->size[1][2] = PURPLE;
		piece->size[1][3] = PURPLE;
		break;
	}
}


void ClearPiece( sPiece* const piece )
{
	unsigned long int x = 0, y = 0;
	for(x = 0; x < 4; ++x)
		for(y = 0; y < 4; ++y)
			piece->size[x][y] = NODRAW;
}

void CopyPiece( sPiece* to, sPiece* const from )
{
	unsigned long int x = 0, y = 0;
	for(x = 0; x < 4; ++x)
		for(y = 0; y < 4; ++y)
			to->size[x][y] = from->size[x][y];
}

const Bool CollisionTest( const long int nx, const long int ny ) 
{
	long int newx = gPiece.x + nx;
	long int newy = gPiece.y + ny;

	long int x = 0, y = 0;

	//if ((nx < 0) || (ny < 0))
	//	return True;

	for(x = 0; x < 4; ++x)
		for(y = 0; y < 4; ++y)
			if(gPiece.size[x][y] != NODRAW)
				if((newx + x < 0) || (newx + x > MAPWIDTH - 1) || (newy + y < 0) || (newy + y > MAPHEIGHT - 1))
					return True;

	for(x = 0; x < MAPWIDTH; ++x)
		for(y = 0; y < MAPHEIGHT; ++y)
			if(x >= newx && x < newx + 4)
				if((y >= newy) && (y < newy + 4))
					if(gMap[x][y] != BLACK)
						if(gPiece.size[x - newx][y - newy] != NODRAW)
							return True;
	return False;
}

void RemoveRow( const unsigned long int row )
{
	unsigned long int x = 0, y = 0;
	for(x = 0; x < MAPWIDTH; ++x)
		for(y = row; y > 0; --y)
			gMap[x][y] = gMap[x][y-1];
}