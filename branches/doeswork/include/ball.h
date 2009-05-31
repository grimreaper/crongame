#ifndef BALL_H
#define BALL_H

#include <allegro.h>
#include "paddle.h"
#include "gamefield.h"

// maximun speed
const int BALL_MAX_SPD = 12;

// minimun speed
const int BALL_MIN_SPD = 5;

class Ball
{	
	public:
		// Operations
		Ball();
		~Ball();
		void init();
		bool update(Paddle &paddle, GameField &game_field);
		void render(BITMAP * bmp);

		// Attributes
		
		// position
		float x;
		float y;
		
		// direction (speed in x,y)
		float dx;
		float dy;
		
		// radius
		int r;
		
		// color
		RGB c;
		
		// time of the ball to be "sticky" to paddle... after this time ,the ball releases... given in tick counts
		int sticky_time; 
			
	private:
		void bounce_x();
		void bounce_y();
};

#endif
