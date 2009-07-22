#ifndef BRICK_H
#define BRICK_H

#include "common.h"
#include "krandom.h"
#include "power.h"

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

		power::brickStatus status;

		void add_life(); //add one life to brick
		void rem_life(); //rem 1 life from brick
		void kill_brick(); //set life to 0
		void set_life(int toWhat); //set life equal to some number
		int get_life();

		// While we could always find out what the current status is
		// of the brick - the question is do we want the status to
		// cause any change. This function should only return a status
		// when its ready to let the user activate it.
		// (As of now when life <=1)
		power::brickStatus getUsableStatus();

	private:
		void make_brick(int level);
		int life; // life, in ball hits
};
#endif
