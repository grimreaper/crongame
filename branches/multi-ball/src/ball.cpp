#include "ball.h"
double deg2rad (double rads);

Ball::Ball()
{}

Ball::~Ball()
{}


void Ball::init()
{
	x = SCREEN_W / 2;
	y = SCREEN_H / 2;

	dx = rand_sign_switch(rand_ex_f(BALL_MIN_SPD,BALL_MAX_SPD ));
	dy = rand_ex_f(BALL_MIN_SPD ,BALL_MAX_SPD );

	r = 8;

	c.r = 0;
	c.g = 0;
	c.b = 255;

	sticky_time = 0;

	status = normal;

	ball_speed_mult = 1.0;
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

		if (sticky_time <= 0 || controls::release_ball_from_paddle())  // time is up?
		{
			// do the up release
			dy = -rand_ex_f(BALL_MIN_SPD ,BALL_MAX_SPD );
			dx = rand_sign_switch(rand_ex_f(BALL_MIN_SPD,BALL_MAX_SPD ));
			// In case we released early (for example from mouse button click) lets set time to zero.
			sticky_time = 0;
		}
		return false; // we are stick to the paddle. all OK
	}
	else
	{
		sticky_time = 0;
	}
	// upgrade ball position with speed x,y
	x += dx * ball_speed_mult;
	y += dy * ball_speed_mult;

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
		return true; // oops >;^)  happens

		y = SCREEN_H - r;
		bounce_y();
	}

	// bounce on paddle, only if going down =P
	if (x + r > paddle.x &&
		x - r < paddle.x + paddle.w &&
		(y + r > paddle.y  || y + r > paddle_last_y  ) &&
		(y - r < paddle.y + paddle.h || y - r < paddle_last_y + paddle.h))
	{
		std::cout << "I just hit paddle at (" << x << "," << y << ") r=" << r <<" where paddle is (" << paddle.x << ","<< paddle.y << ") with dimensions of " << paddle.w << "x" << paddle.h <<std::endl;
		std::cout << paddle.x << "|" <<paddle.x + (paddle.w/3) << "|" << paddle.x + (paddle.w/3)*2  << "|" << paddle.x + paddle.w << std::endl;
		if (x - r < paddle.x + (paddle.w / 3))
		{
			std::cout << "In the first third";
			bounce_y();

		}
		if (x - r > paddle.x + (paddle.w / 3) && x -r < paddle.x + (paddle.w/3)*2 )
		{
			std::cout << "In the mid third";
			bounce_y();
		}
		if (x - r > paddle.x + (paddle.w/3)*2)
		{
			std::cout << "In the final third";
			bounce_y();
		}

		std::cout << std::endl;
		y = paddle.y - r; // this is lame safe check

	}

	bool hitX = false;
	bool hitY = false;
	Power::brickStatus whatBrickStatus;

	// bounce and hit on bricks
	if (game_field.ball_hit_brick((int)x-r,(int)y))
	{
		hitX = true;
		whatBrickStatus = game_field.getBrickStatus((int)x-r,(int)y);
	}
	if (game_field.ball_hit_brick((int)x+r,(int)y))
	{
		hitX = true;
		whatBrickStatus = game_field.getBrickStatus((int)x+r,(int)y);

	}
	if (game_field.ball_hit_brick((int)x,(int)y-r))
	{
		hitY = true;
		whatBrickStatus = game_field.getBrickStatus((int)x,(int)y-r);
	}
	if (game_field.ball_hit_brick((int)x,(int)y+r))
	{
		hitY = true;
		whatBrickStatus = game_field.getBrickStatus((int)x,(int)y+r);
	}
	if((hitX && status != on_fire) || whatBrickStatus == Power::unbreakable)
	{
		bounce_x();
	}
      if((hitY && status != on_fire) || whatBrickStatus == Power::unbreakable)
	{
		bounce_y();
	}
	if (hitX || hitY)
	{
		std::cout << "we know that the brick is status # " << whatBrickStatus << " and that ball is " << status;
		doPowerUp(whatBrickStatus);
		paddle.doPowerUp(whatBrickStatus);
		game_field.doPowerUp(whatBrickStatus);
		switch (whatBrickStatus)
		{
			case Power::add_live:
				// I really should make the field call a briuck function - but atm I want to keep everything together
				// or even better - figure out a better method of dealing with statuses and keeping encapsulation
				//++lives;
				break;
			default:
				break;
		}
	}
	c.r = status * 10;
	c.b = (status == normal) ? 255 : 100;
	c.r = (status == on_fire) ? 255 : status;

	// never go faster than paddle size, or we are screwed :P
	dy = std::min (dy,  paddle.h*0.25);
	dy = std::max (dy, -paddle.h*0.25);

	dx = std::min (dx,  paddle.w*0.25);
	dx = std::max (dx, -paddle.w*0.25);

	paddle_last_y = paddle.y; // save our last position

	c.b = 255 - (status * 30);
	c.r = 0 + status * 30;
	c.g = 0;

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

	if (arc4rand() % 100 < 10)
	{
		dx = rand_sign_switch(rand_ex_f(BALL_MIN_SPD , BALL_MAX_SPD ));
	}
}


//angle defaults to -1
void Ball::bounce_y(int angle)
{
//	if (angle == -1)
//	{
		dy = -rand_ex_f(dy * 0.9, dy*1.1);
//	}
//	std::cout << -std::sin(deg2rad(angle)) << std::endl;
//	dy = -std::sin(deg2rad(angle));

//	if (rand() % 100 < 10)
//		dy = rand_sign_switch(rand_ex_f(BALL_MIN_SPD , BALL_MAX_SPD ));
}

//move this to a math file
double deg2rad (double rads)
{
	static double pi = 3.141592653589793238;
	return ((pi * rads) / 180);
}

void Ball::doPowerUp(Power::brickStatus toDo)
{
	int minusAmount = (r >= 8) ? 4 : 2;
	switch (toDo)
	{
		case Power::standard:
			break;
		case Power::make_all_normal:
			status = normal;
			r = 8;
			c.r = c.g = 0;
			c.b = 255;
			break;
		case Power::make_ball_fire:
			status = on_fire;
			break;
		case Power::make_ball_big:
			if (r <= 20)
			{
				r += 4;
			}
			break;
		case Power::make_ball_small:
			if (r > 2)
			{
				r -= minusAmount;
			}
			break;
		//For speed up and slow down - don't make too much of change.
		case Power::make_ball_fast:
			ball_speed_mult += 0.02;
			break;
		case Power::make_ball_slow:
			ball_speed_mult -= 0.02;
			break;
		default:
			break;
	}
}
