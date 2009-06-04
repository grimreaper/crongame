#ifndef BRICK_H
#define BRICK_H

#include "common.h"
#include "krandom.h"

class Brick
{
	public:
		// Operations
		Brick();
		Brick(int lvl);
		~Brick();

		void update();
		void render(BITMAP * bmp);

		// Attributes
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

		void add_life(); //add one life to brick
		void rem_life(); //rem 1 life from brick
		void kill_brick(); //set life to 0
		void set_life(int toWhat); //set life equal to some number
		int get_life();

		log *logger;

	private:
		void make_brick(int level);
		int life; // life, in ball hits
};

#endif
