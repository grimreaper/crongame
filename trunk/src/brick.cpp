#include "brick.h"

Brick::Brick(int level)
{
	make_brick(level);
}

Brick::Brick(): life (0), w (32), h(32), status (power::standard)
{
	make_brick(1);
}

void Brick::make_brick(int lvl)
{
	c.r = c.g = c.b = 128;
	// we want the % value to be slightly higher than the number of power
	// bricks - I want to find an automatic way to do this... TODO
	status = power::generateStatus();
}

Brick::~Brick()
{}


void Brick::update()
{
	c.b = 0;
	c.g = 255 - ((life <= 10) ? life * 20 : 254);
	c.r = status * 100;
	// not much to be done here yet... common' is a brick, what you expect ? :P
}

void Brick::render(BITMAP *bmp)
{
	if (life < 1)
	{
		return; // we don't draw broken bricks
	}

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

/*
	most of these functions are not really needed - I'm only using it until I move over all relevent functionality to the brick class itself
*/

void Brick::set_life(int toWhat)
{
	life = toWhat;
}

int Brick::get_life()
{
	return life;
}

void Brick::rem_life()
{
	--life;
}
