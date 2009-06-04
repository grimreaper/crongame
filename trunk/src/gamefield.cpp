#include "gamefield.h"
#include <iostream>

GameField::GameField() : w(0), h(0), bc(0)
{
	int i;
	bricks.resize(GAMEFIELD_MAX_H);
	for (i = 0; i < bricks.size(); ++i)
	{
		bricks[i].resize(GAMEFIELD_MAX_W);
	}
}

GameField::~GameField()
{}

// creates a new level

void GameField::do_new_random_level(int w, int h, int level)
{
	int i;
	for (i = 0; i < bricks.size(); ++i)
	{
		 bricks[i].clear();
	}

/*	bricks.resize(h);
	for (i = 0; i < bricks.size(); ++i)
	{
		bricks[i].resize(w);
	}*/
	if (w < 1 || w > GAMEFIELD_MAX_W)
	{
		w = GAMEFIELD_MAX_W; // safe check
	}
	if (h < 1 || h > bricks.size())
	{
		h = bricks.size(); // safe check
	}

	this->w = w;
	this->h = h;
	bc = 0;

	// fill the matrix with random level
	for (int y = 0 ; y <  h; ++y)
	{
		for (int x = 0 ; x < w; ++x)
		{
			//this should be done as part of the brick class - no the game_field class */
			bricks[x][y] = Brick(level);

			bricks[x][y].x = x * SCREEN_W / w;
			bricks[x][y].y = y * SCREEN_H / 3 / h;

			bricks[x][y].w = SCREEN_W / w;
			bricks[x][y].h = SCREEN_H / 3 / h;

			// pick a random color
			bricks[x][y].c.r = rand_ex_i(128, 255);
			bricks[x][y].c.g = rand_ex_i(128, 255);
			bricks[x][y].c.b = rand_ex_i(128, 255);

			++bc; // count bricks (lame)
		}
	}


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

	Brick *which_brick = px_to_brick(x_px, y_px);

	if (which_brick->get_life() > 0)
	{
		which_brick->rem_life();

		if (which_brick->get_life() <= 0)
		{
			--bc; // wasted brick!
		}

		return true; // hit!
	}

	return false;
}

Brick::brickStatus GameField::getBrickStatus (int x_px , int y_px)
{
	Brick *which_brick = px_to_brick(x_px, y_px);
	if (which_brick->get_life() <= 0)
	{
		//only give power when dead
		return which_brick->status;
	}
	return Brick::standard;
}
Brick* GameField::px_to_brick(int x_px , int y_px)
{
	int w_b = SCREEN_W / w;
	int h_b = SCREEN_H / 3 / h;
	int which_x = x_px / w_b;
	int which_y = y_px / h_b;
	return &bricks[which_x][which_y];
}
