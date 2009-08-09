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

		void move(int x, int y);

		int w; // size, in pixels
		int h;

		RGB c; // color, in R,G,B

		Power::brickStatus status;

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
		Power::brickStatus getUsableStatus();

		void doPowerUp(Power::brickStatus doWhat);

	private:
		void make_brick(int level);
		/*! \brief Every time we lose a life or certain other events happen we have to fix the color */
		void fixColor();
		int life; // life, in ball hits

		/*! \var If we are gray we need to know that so that when we lose a life we don't go crazy */
		static bool isGray;

		/*! \var Attributes */
		int x; // position, in pixels
		int y;

};
#endif
