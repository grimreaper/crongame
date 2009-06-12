#ifndef GAME_H
#define GAME_H

#include "game_status_constants.h"
#include "ball.h"
#include <iostream>
#include "paddle.h"

class Game
{
	public:
		Game();
		~Game();

		//start a completely new game
		void init_game();
		//restart level - from the top
		void restart_level();
		//continue level - returns ball and such to starting
		//position - but not the field.
		void continue_level();

		//we move on to the next level
		void next_level();
		//we just lost a life
		int lost_life();

		int lives;
		int level;

	private:

};
#endif
