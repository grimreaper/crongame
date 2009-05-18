#include "gamefield.h"
#include "krandom.h"

GameField::GameField() : w (0), h (0), bc (0)
{}

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

	// fill the matrix with random level
	for (int y = 0 ; y < h; y++)
	{
		for (int x = 0 ; x < w; x++)
		{
			bricks[x][y].life = arc4random() % max_life + 1;

			bricks[x][y].x = x * SCREEN_W / w;
			bricks[x][y].y = y * SCREEN_H / 3 / h;

			bricks[x][y].w = SCREEN_W / w;
			bricks[x][y].h = SCREEN_H / 3 / h;

			// pick a random color
			bricks[x][y].c.r = rand_ex_i(128, 255);
			bricks[x][y].c.g = rand_ex_i(128, 255);
			bricks[x][y].c.b = rand_ex_i(128, 255);

			++bc; // count bricks (lame) - use the standard vector functions - maybe ?
		}
	}


}

// returns true if we finished the level (0 bricks left)
bool GameField::update()
{
	return (bool) (bc < 1);
}

void GameField::render(BITMAP *bmp)
{
	for (int y = 0 ; y < h; y++)
	{
		for (int x = 0 ; x < w; x++)
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

	if (y_px < 0 ||
	        x_px < 0 ||
	        y_px / h_b > h ||
	        x_px / w_b > w)
		return false; // ball too low or out of bounds

	if (bricks[x_px / w_b][y_px / h_b].life > 0)
	{
		bricks[x_px / w_b][y_px / h_b].life--;

		if (bricks[x_px / w_b][y_px / h_b].life <= 0)
		{
			--bc; // wasted brick!
		}

		return true; // hit!
	}

	return false;
}
