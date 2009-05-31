#include "brick.h"

Brick::Brick()
{
	c.r = c.g = c.b = 128;
	w = h = 32;
	life = 0;
}

Brick::~Brick()
{}


void Brick::update()
{
	// not much to be done here yet... common' is a brick, what you expect ? :P
}

void Brick::render(BITMAP *bmp)
{
	if (life < 1)
		return; // we don't draw broken bricks
	
	if (w > 12 && h > 12) // check if the brick is big enough to shadow it
	{
		// render with shadow
		rectfill(bmp, x, y, x + w, y + h, makecol((int)(c.r*0.8), (int)(c.g*0.8), (int)(c.b*0.8)));
		rectfill(bmp, x+3, y+3, x + w-3, y + h-3, makecol((int)(c.r*0.9), (int)(c.g*0.9), (int)(c.b*0.9)));
		rectfill(bmp, x+6, y+6, x + w-6, y + h-6, makecol(c.r, c.g, c.b));
	}
	else
	{
		// render normal
		rectfill(bmp, x, y, x + w, y + h, makecol(c.r, c.g, c.b));
	}

}

