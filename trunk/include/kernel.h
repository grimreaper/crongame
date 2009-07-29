#ifndef KERNEL_H
#define KERNEL_H

#include "common.h"

#include "paddle.h"
#include "ball.h"
#include "gamefield.h"
#include "mtimer.h"
#include "game.h"
#include "gerror.h"
#include "controls.h"

#include "game_status_constants.h"

class Kernel
{
	public:
		// Operations
		Kernel(); // constructor
		~Kernel(); // destructor
		Kernel(const Kernel&);
		Kernel operator=(const Kernel&);

		void init(); // inits the game
		void play(); // plays the main game loop
		void shutdown(); // ends the game

		// Attributes
  		BITMAP *double_buffer; // the double buffer bitmap
		Paddle paddle; // the player paddle

		int lives; //number of lives left

		Game mygame;

	private:
		void init_game(); // this inits the game without reseting the kernel or the level, is used for when you start a new level, lose a life, etc
		void restart_game(); // restart the game - not just continue.
		int update(); // updates game logic
		void render(); // updates graphics of the game

};

#endif
