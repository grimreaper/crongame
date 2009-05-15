
#ifndef KERNEL_H
#define KERNEL_H

#include <allegro.h>

/*#include "paddle.h"
#include "ball.h"
#include "gamefield.h"
#include "mtimer.h"*/


// some states of the update of the game (this is NOT bitmask values)

// all fine
#define KERNEL_UDP_OK 0

// go to next level
#define KERNEL_UDP_NEXT_LEVEL 1

// lost a life
#define KERNEL_UDP_LOST_LIFE 2

// pause
#define KERNEL_UDP_PAUSE 100

// exit from game (to menu)
#define KERNEL_UDP_EXIT 101

// exit to operating system (DOS ? :P)
#define KERNEL_UDP_QUIT 102



class Kernel
{
	public:
		// Operations
		Kernel(); // constructor
		~Kernel(); // destructor

		void init(); // inits the game
		void play(); // plays the main game loop
		void shutdown(); // ends the game

		// Attributes
  		BITMAP *double_buffer; // the double buffer bitmap
/*		Paddle paddle; // the player paddle 
		Ball ball; // the game ball
		GameField game_field; // the game field */

	private:
		void init_game(); // this inits the game without reseting the kernel or the level, is used for when you start a new level, lose a life, etc
		int update(); // updates game logic
		void render(); // updates graphics of the game
};

#endif
