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
#ifndef _BLOCK_H_
#define _BLOCK_H_

/***  Custom Header Files  ***/
#include "sPiece.h"
#include "eBool.h"

void NewBlock( const Bool start );
void DownBlock( void );
void MoveBlock( const long int x, const long int y); //coordinates to move.
void RotateBlock( void );

void GenBlock( sPiece* const piece );
void ClearPiece( sPiece* const piece );
void CopyPiece( sPiece* to, sPiece* const from );

const Bool CollisionTest( const long int nx, const long int ny); //test collision of blocks
void RemoveRow( const unsigned long int row); //remove a row.. that would be the 'x'.

#endif/// END IFNDEF _BLOCK_H_