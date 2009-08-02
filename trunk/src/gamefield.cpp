#include "gamefield.h"

/*!
	\todo Make a dorEachFunction that takes a pointer to a function and runs it on every brick. It shouldn't be /that/ hard
*/

GameField::GameField() : w(0), h(0), bc(0)
{
}

GameField::~GameField()
{}

// creates a new max_life

void GameField::do_new_random_level(int level)
{

	// I think we cleared the level like this. At the minimum  the bug with bouncing on non-existant bricks seems to go away
	for (int y = 0 ; y < GAMEFIELD_MAX_H; ++y)
	{
		for (int x = 0 ; x < GAMEFIELD_MAX_W; ++x)
		{
			bricks[x][y].set_life(0);
		}
	}

	int max_life = std::min(level, 5);
	w = 3 + rand() % level + level;
	h = 3 + rand() % level;
	// pick new level parameters
	//don't let mygame.lives of bricks go greater than 5
	w = std::min (w, GAMEFIELD_MAX_W-2);
	h = std::min (h, GAMEFIELD_MAX_H-2);

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
	// if we could do that then pre-building max_lifes should be even easier.

	int blank_spots = max_life;
	int min_life = 0;
	Brick *which_brick = NULL;

	// fill the matrix with random max_life
	for (int y = 0 ; y < h; ++y)
	{
		for (int x = 0 ; x < w; ++x)
		{
			bricks[x][y] = Brick(level);
			which_brick = &bricks[x][y];

			//this should be done as part of the brick class - no the game_field class */
			which_brick->set_life (arc4rand() % max_life + min_life);
			if (which_brick->get_life() == 0)
			{
				--blank_spots;
			}
			else
			{
				if (which_brick->status != Power::unbreakable)
				{
					++bc;
				}
			}
			if (blank_spots == 0)
			{
				min_life = 1;
			}

			which_brick->x = x * SCREEN_W / w;
			which_brick->y = y * SCREEN_H / 3 / h;

			which_brick->w = SCREEN_W / w;
			which_brick->h = SCREEN_H / 3 / h;

			// pick a random color
/*			which_brick->c.r = rand_ex_i(128, 255);
			which_brick->c.g = rand_ex_i(128, 255);
			which_brick->c.b = rand_ex_i(128, 255);
*/

		}
	}
	std::cout << "And our final bc is " << bc << std::endl;
}

// returns true if we finished the max_life (0 bricks left)
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
		std::cout << "I just hit a brick at px (x,y) (" << x_px << "," << y_px << ") starting at (x,y) with a (w,h) of (" << bricks[which_x][which_y].x \
			<< ","<< bricks[which_x][which_y].y << ")/("<<bricks[which_x][which_y].w << "," <<bricks[which_x][which_y].h << ")";
		if (bricks[which_x][which_y].get_life() <= 0)
		{
			std::cout << " and its now dead!" << std::endl;
			--bc; // wasted brick!
			std::cout << " The new bc is " << bc;
			std::cout << std::endl;
		}

		return true; // hit!
	}

	return false;
}

Power::brickStatus GameField::getBrickStatus (int x_px , int y_px)
{
	Brick *which_brick = px_to_brick(x_px, y_px);
	return which_brick->getUsableStatus();
}

Brick* GameField::px_to_brick(int x_px , int y_px)
{
	int w_b = SCREEN_W / w;
	int h_b = SCREEN_H / 3 / h;
	int which_x = x_px / w_b;
	int which_y = y_px / h_b;
	return &bricks[which_x][which_y];
}

void GameField::doPowerUp(Power::brickStatus doWhat)
{
	for (int y = 0 ; y < h; ++y)
	{
		for (int x = 0 ; x < w; ++x)
		{
			bricks[x][y].doPowerUp(doWhat);
		}
	}
}
