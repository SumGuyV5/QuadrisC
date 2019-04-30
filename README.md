/*	Copyright (C) 2011 Richard W. Allen
	Program Name:	Quadris C
	Author:		Richard W. Allen
	Version:	V1.1
	Date Started:	January 24, 2011
	Date End:	March 02, 2011
	Updated:	December 15, 2011
	Webpage:	http://www.richardallenonline.com
	IDE:		Visual Studio 2010 (Windows 7), Code::Blocks 10.05 (Ubuntu 10.04 LTS)
	Compiler:	C\C++ 2010 (Windows 7), gcc 4.4.3 (Ubuntu 10.04 LTS), devkitPPC 1.5.0 (Wii)
	Langage:	C
	License:	GNU GENERAL PUBLIC LICENSE Version 2
			see license.txt for details

	Quadris C Copyright (C) 2011 Richard W. Allen 
	Comes with ABSOLUTELY NO WARRANTY;
	Quadris C is licensed under the GNU GENERAL PUBLIC LICENSE Version 2.
	for details see the license.txt include with this program.
*/
***************************************************************/
Instructions

Use the up arrow key to rotate the piece.
Use the down arrow key to accelerate the piece.
Use the left and right arrow keys to move the piece left or right.

***************************************************************/
Instructions Wii

Turn your wiimote sideways.

Use the D-pad up to rotate the piece.
Use the D-pad down to accelerate the piece.
Use the D-pad left and right to move the piece left or right.
    
Use the home button to exit the game.

***************************************************************/
Installing instructions for the Wii

You must first setup homebrew
http://wiibrew.org/wiki/Homebrew_setup

unzip the QuadricCWii.zip in the apps directory of your SD card.

***************************************************************/
Library's used.

SDL 1.2.14 http://www.libsdl.org
SDL Image 1.2.10 http://www.libsdl.org/projects/SDL_image/
SDL Mixer 1.2.11 http://www.libsdl.org/projects/SDL_mixer/
SDL TFF 2.0.9 http://www.libsdl.org/projects/SDL_ttf/

SDL Wii http://wiibrew.org/wiki/SDL_Wii

***************************************************************/
Chanages.

Ported to Wii using SDL Wii and devkitpro.
changed to drop speed from 250 to 50.
changed playing area from 30 blocks to 28.
add joystick support.