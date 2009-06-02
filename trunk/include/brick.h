#ifndef BRICK_H
#define BRICK_H

#include <allegro.h>
#include "krandom.h"

class Brick
{
	public:
		// Operations
		Brick();
		Brick(int level);
		~Brick();

		void update();
		void render(BITMAP * bmp);

		// Attributes
		int life; // life, in ball hits

		int x; // position, in pixels
		int y;

		int w; // size, in pixels
		int h;

		RGB c; // color, in R,G,B

		enum brickStatus
		{
			standard,
			make_all_normal,
			make_ball_fire,
			add_live, //yes I am aware that this is not proper English - I am using lives and lifes differently
			make_ball_big,
			make_ball_small,
			no_see_paddle
		};

		brickStatus status;

	private:
		void make_brick(int level);
};

#endif
