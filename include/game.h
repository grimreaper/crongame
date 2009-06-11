#ifndef GAME_H
#define GAME_H

#include "paddle.h"
#include "ball.h"

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

		Paddle paddle; // the player paddle
		Ball ball; // the game ball

		int lives;
		int level;

	private:

};
#endif
