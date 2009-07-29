#include "paddle.h"

void Paddle::init()
{
	// lame default values... DEBUG - this should be better done
	w = static_cast<int> (SCREEN_W * 0.20);
	h = static_cast<int> (SCREEN_H * 0.05);

	x = SCREEN_W / 2;
	y = SCREEN_H - h - 10;

	// paddle color
	c.r = 0;
	c.g = 0;
	c.b = 255;

}

// updates control of paddle
void Paddle::update()
{
	// mouse control... little lame
	x = mouse_x - (w / 2);
	//y = mouse_y - (h / 2); // I disabled the Y movement for now -- DEBUG

	y = std::max(static_cast<float> (SCREEN_H - (SCREEN_H / 3)), y);
	y = std::min (static_cast<float> (SCREEN_H - h), y);

	x = std::max(static_cast<float> (0), x);
	x = std::min(static_cast<float> (SCREEN_W - w), x);

}

void Paddle::render( BITMAP * bmp )
{

	rectfill(bmp, (int)x, (int)y, (int)x + w, (int)y + h, makecol((int)(c.r*0.6), (int)(c.g*0.6), (int)(c.b*0.6)));
	rectfill(bmp, (int)x+2, (int)y+2, (int)x + w-2, (int)y + h-2, makecol((int)(c.r*0.7), (int)(c.g*0.7), (int)(c.b*0.7)));
	rectfill(bmp, (int)x+4, (int)y+4, (int)x + w-4, (int)y + h-4, makecol((int)(c.r*0.8), (int)(c.g*0.8), (int)(c.b*0.8)));
	rectfill(bmp, (int)x+6, (int)y+6, (int)x + w-6, (int)y + h-6, makecol((int)(c.r*0.9), (int)(c.g*0.9), (int)(c.b*0.9)));

	rectfill(bmp, (int)x + 8, (int)y + 8, (int)x + w - 8, (int)y + h - 8, makecol(c.r, c.g, c.b));
}

void Paddle::reset_color()
{
	c.b = 255;
	c.g = c.r =0;
}

void Paddle::doPowerUp(power::brickStatus toDo)
{
	switch (toDo)
	{
		case power::standard:
			break;
		case power::make_all_normal:
			reset_color();
			break;
		case power::no_see_paddle:
			c.r = 10;
			c.g = 10;
			c.b = 10;
			break;
		case power::make_paddle_small:
			// We don't want to go to small.
			w = std::max(w - 5, 5);
			break;
		case power::make_paddle_big:
			// Don't get too big on me.
			w = std::min(50, w + 5);
			break;
		case power::make_paddle_zero:
			// Lets get a 1 pixel paddle.
			w = 1;
			break;
		case power::make_paddle_giant:
			// Lets get a giant paddle.
			w = 100;
			break;
		default:
 			break;
	}
}

void Paddle::getMouse()
{
	position_mouse((int)x + (w/2), (int)y + (h/2)); // put the mouse cursor in paddle
}

Paddle::Paddle()
{
	init();
}

Paddle::~Paddle()
{}
