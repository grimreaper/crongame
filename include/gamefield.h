#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <allegro.h>
#include "brick.h"
#include "power.h"

// max w & h in bricks
const int  GAMEFIELD_MAX_W = 10;
const int  GAMEFIELD_MAX_H = 10;

class GameField
{
	public:
		// Operations
		GameField();
		~GameField();

		void do_new_random_level(int w, int h, int max_life); // creates a new level size w*h, with 1..maxlife for bricks

		bool update();
		void render(BITMAP *bmp);

		bool ball_hit_brick(int x_px , int y_px); // this is used by the ball to hit the bricks, returns true if a brick was hit

		power::brickStatus getBrickStatus(int x_px , int y_px);

		// Attributes

		Brick bricks[GAMEFIELD_MAX_W][GAMEFIELD_MAX_H];
		int w, h; // current width and height in bricks, must be < GAMEFIELD_MAX_*
		int bc; // brick count, when bc==0, next level

	private:
		Brick* px_to_brick(int x_px , int y_px); //return a reference to a brick
};

#endif
