#ifndef PADDLE_H
#define PADDLE_H

#include "common.h"
#include "paddle.h"
#include "power.h"
#include "controls.h"

class Paddle
{
	public:
		// Operations
		Paddle();
		~Paddle();
		void init();
		void update();
		void render(BITMAP * bmp);
		void reset_color();

		void doPowerUp(Power::brickStatus toDo);

		void getMouse(); // moves the cursor to the center of the paddle.

		// Attributes
		float x;
		float y;
		int w;
		int h;
		RGB c;
};

#endif
