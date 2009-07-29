#ifndef KERNEL_H
#define KERNEL_H

#include "common.h"

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

		Game mygame;

	private:
		void restart_game(); // restart the game - not just continue.
		int update(); // updates game logic
		void render(); // updates graphics of the game

};

#endif
