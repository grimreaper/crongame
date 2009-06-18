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
	c.g = 0;
	c.b = 255;

}

// updates control of paddle
void Paddle::update()
{
	// mouse control... little lame
	x = mouse_x - (w / 2);
	//y = mouse_y - (h / 2); // I disabled the Y movement for now -- DEBUG

	y = std::max((float)(SCREEN_H - (SCREEN_H / 3)), y);
	y = std::min ((float)(SCREEN_H - h), y);

	x = std::max((float)(0), x);
	x = std::min((float)(SCREEN_W - w), x);

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

Paddle::Paddle()
{
	init();
}

Paddle::~Paddle()
{}

