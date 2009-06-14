#include "gamefield.h"
#include <iostream>

GameField::GameField() : w(0), h(0), bc(0)
{
}

GameField::~GameField()
{}

// creates a new level

void GameField::do_new_random_level(int w, int h, int max_life)
{
	if (w < 1 || w > GAMEFIELD_MAX_W)
	{
		w = GAMEFIELD_MAX_W; // safe check
	}
	if (h < 1 || h > GAMEFIELD_MAX_H)
	{
		h = GAMEFIELD_MAX_H; // safe check
	}

	this->w = w;
	this->h = h;
	bc = 0;

	// I want to see if we could deal with having a 0-life brick.
	// if we can then making special arragments shouldn't be that hard.
	// TODO - allow for width to be dynamically chosen
	// if we could do that then pre-building levels should be even easier.

	int blank_spots = max_life;
	Brick *which_brick = NULL;

	// fill the matrix with random level
	for (int y = 0 ; y < h; ++y)
	{
		for (int x = 0 ; x < w; ++x)
		{
			which_brick = &bricks[x][y];

			//this should be done as part of the brick class - no the game_field class */
			which_brick->set_life (arc4rand() % max_life);

			which_brick->x = x * SCREEN_W / w;
			which_brick->y = y * SCREEN_H / 3 / h;

			which_brick->w = SCREEN_W / w;
			which_brick->h = SCREEN_H / 3 / h;

			// pick a random color
/*			which_brick->c.r = rand_ex_i(128, 255);
			which_brick->c.g = rand_ex_i(128, 255);
			which_brick->c.b = rand_ex_i(128, 255);
*/
			if (which_brick->get_life() == 0)
			{
				if (blank_spots > 0)
				{
					--blank_spots;
				}
				else
				{
					which_brick->set_life ( arc4rand() % max_life + 1 );
					++bc;
				}
			}
			else
			{
				++bc; // count bricks (lame)
			}
			if (which_brick->status == power::unbreakable)
			{
				--bc;
				std::cout << "I'm unbreakable - remove a bc!" << std::endl;
			}
		}
	}
	std::cout << "And our final bc is " << bc << std::endl;
}

// returns true if we finished the level (0 bricks left)
bool GameField::update()
{
	for (int y = 0 ; y < h; ++y)
	{
		for (int x = 0 ; x < w; ++x)
		{
			bricks[x][y].update();
		}
	}
	return (bool)(bc < 1);
}

void GameField::render(BITMAP *bmp)
{
	for (int y = 0 ; y < h; ++y)
	{
		for (int x = 0 ; x < w; ++x)
		{
			bricks[x][y].render(bmp);
		}
	}
}

bool GameField::ball_hit_brick(int x_px , int y_px)
{
	// this is used by the ball to hit the bricks, returns true if a brick was hit
	int w_b = SCREEN_W / w;
	int h_b = SCREEN_H / 3 / h;

	if (y_px < 0 || x_px < 0 || y_px / h_b > h || x_px / w_b > w)
	{
		return false; // ball too low or out of bounds
	}
	int which_x = x_px / w_b;
	int which_y = y_px / h_b;

	if (bricks[which_x][which_y].get_life() > 0)
	{
		bricks[which_x][which_y].rem_life();

		if (bricks[which_x][which_y].get_life() <= 0)
		{
			--bc; // wasted brick!
		}

		return true; // hit!
	}

	return false;
}

power::brickStatus GameField::getBrickStatus (int x_px , int y_px)
{
	Brick *which_brick = px_to_brick(x_px, y_px);
	if (which_brick->get_life() <= 0)
	{
		//only give power when dead
		return which_brick->status;
	}
	return power::standard;
}
Brick* GameField::px_to_brick(int x_px , int y_px)
{
	int w_b = SCREEN_W / w;
	int h_b = SCREEN_H / 3 / h;
	int which_x = x_px / w_b;
	int which_y = y_px / h_b;
	return &bricks[which_x][which_y];
}
