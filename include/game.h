#ifndef GAME_H
#define GAME_H

#include "common.h"
#include "game_status_constants.h"
#include "ball.h"
#include "paddle.h"
#include "dialog.h"
#include "gamefield.h"
#include "mtimer.h" //For the timer constants

extern int flag_cheat;

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
		// or we just move back
		void prev_level();

		//we just lost a life
		int lost_life();

		int lives;
		int level;

		Ball ball; //The game ball - when we allow multiple balls this method of storing balls has to change.
		GameField game_field; // the game field

	private:

};
#endif
