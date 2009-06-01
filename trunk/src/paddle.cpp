#include "paddle.h"

void Paddle::init()
{
	// lame default values... DEBUG - this should be better done
	w = (int)(SCREEN_W * 0.20);
	h = (int)(SCREEN_H * 0.05);

	x = SCREEN_W / 2;
	y = SCREEN_H - h - 10;

	// paddle color
	c.r = 0;
	c.g = 128;
	c.b = 200;

}

// updates control of paddle
void Paddle::update()
{
	// mouse control... little lame
	x = mouse_x - (w / 2);
	//y = mouse_y - (h / 2); // I disabled the Y movement for now -- DEBUG

	if (y < SCREEN_H - (SCREEN_H / 3))
		y = SCREEN_H - (SCREEN_H / 3);

	if (y > SCREEN_H - h)
		y = SCREEN_H - h;

	if (x < 0)
		x = 0;

	if (x > SCREEN_W - w)
		x = SCREEN_W - w;

}

void Paddle::render( BITMAP * bmp )
{

	rectfill(bmp, (int)x, (int)y, (int)x + w, (int)y + h, makecol((int)(c.r*0.6), (int)(c.g*0.6), (int)(c.b*0.6)));
	rectfill(bmp, (int)x+2, (int)y+2, (int)x + w-2, (int)y + h-2, makecol((int)(c.r*0.7), (int)(c.g*0.7), (int)(c.b*0.7)));
	rectfill(bmp, (int)x+4, (int)y+4, (int)x + w-4, (int)y + h-4, makecol((int)(c.r*0.8), (int)(c.g*0.8), (int)(c.b*0.8)));
	rectfill(bmp, (int)x+6, (int)y+6, (int)x + w-6, (int)y + h-6, makecol((int)(c.r*0.9), (int)(c.g*0.9), (int)(c.b*0.9)));

	rectfill(bmp, (int)x + 8, (int)y + 8, (int)x + w - 8, (int)y + h - 8, makecol(c.r, c.g, c.b));
}

Paddle::Paddle()
{
	init();
}

Paddle::~Paddle()
{}

