#include "ball.h"
#include "krandom.h"

Ball::Ball()
{}

Ball::~Ball()
{}


void Ball::init()
{
	x = SCREEN_W / 2;
	y = SCREEN_H / 2;

	r = 8;

	dx = rand_sign_switch(rand_ex_f(BALL_MIN_SPD,BALL_MAX_SPD ));
	dy = rand_ex_f(BALL_MIN_SPD ,BALL_MAX_SPD );

	sticky_time = 0;

	c.r = 255;
	c.g = 200;
	c.b = 0;
}

// updates ball ... returns true if the ball was lost (we lose a life) 
bool Ball::update(Paddle &paddle, GameField &game_field)
{
	static float paddle_last_y = 0; // we use this so the ball can't go trought the paddle, we interpolate

	if (sticky_time > 0)
	{

		--sticky_time;
		// stick our position to paddle position
		x = paddle.x + paddle.w / 2;
		y = paddle.y - r;

		if (mouse_b & 1) // mouse button is pressed, release the ball
		{
			sticky_time = 0;
		}

		if (sticky_time <= 0)  // time is up?
		{
			// do the up release
			dy = -rand_ex_f(BALL_MIN_SPD ,BALL_MAX_SPD );
			dx = rand_sign_switch(rand_ex_f(BALL_MIN_SPD,BALL_MAX_SPD ));
		}
		return false; // we are stick to the paddle. all OK
	}
	else
	{
		sticky_time = 0;
	}

	// upgrade ball position with speed x,y
	x += dx;
	y += dy;

	// bounce on field bounds
	if (x < r)
	{
		x = r;
		bounce_x();
	}

	if (x > SCREEN_W - r)
	{
		x = SCREEN_W - r;
		bounce_x();
	}

	if (y < r)
	{
		y = r;
		bounce_y();
	}

	if (y > SCREEN_H - r)  // here we DIE ...
	{
		return true;
		/*
		y = SCREEN_H - r;
		bounce_y();
		*/
	}

	// bounce on paddle, only if going down =P
	if (x + r > paddle.x && 
		x - r < paddle.x + paddle.w && 
		(y + r > paddle.y  || y + r > paddle_last_y  ) && 
		(y - r < paddle.y + paddle.h || y - r < paddle_last_y + paddle.h))
	{
			y = paddle.y - r; // this is lame safe check

			bounce_y();
	}


	// bounce and hit on bricks
	if (game_field.ball_hit_brick((int)x-r,(int)y) || game_field.ball_hit_brick((int)x+r,(int)y))
	{
		bounce_x();
	}

	if (game_field.ball_hit_brick((int)x,(int)y-r) || game_field.ball_hit_brick((int)x,(int)y+r))
	{
		bounce_y();
	}


	// never go faster than paddle size, or we are screwed :P
	if (dy > paddle.h*0.25) 
		dy = paddle.h*0.25;
	
	if (dy < -paddle.h*0.25) 
		dy = -paddle.h*0.25;

	if (dx > paddle.w*0.25) 
		dx = paddle.w*0.25;
	
	if (dx < -paddle.w*0.25) 
		dx = -paddle.w*0.25;
	

	paddle_last_y = paddle.y; // save our last position
	
	return false; // all OK for now
}

void Ball::render(BITMAP * bmp)
{
	circlefill(bmp, (int)x, (int)y, r, makecol((int)(c.r*0.6), (int)(c.g*0.6), (int)(c.b*0.6)));
	circlefill(bmp, (int)x, (int)y, r-2, makecol((int)(c.r*0.8), (int)(c.g*0.8), (int)(c.b*0.8)));
	circlefill(bmp, (int)x, (int)y, r-4, makecol(c.r, c.g, c.b));
}


void Ball::bounce_x()
{
	dx = -rand_ex_f(dx * 0.9, dx * 1.1);

	if (rand() % 100 < 10)
		dx = rand_sign_switch(rand_ex_f(BALL_MIN_SPD , BALL_MAX_SPD ));
}


void Ball::bounce_y()
{
	dy = -rand_ex_f(dy * 0.9, dy*1.1);

//	if (rand() % 100 < 10)
//		dy = rand_sign_switch(rand_ex_f(BALL_MIN_SPD , BALL_MAX_SPD ));
}
