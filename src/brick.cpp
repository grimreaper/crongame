#include "brick.h"
bool Brick::isGray = false;

Brick::Brick(int level)
{
	make_brick(level);
}

Brick::Brick(): life (0), w (32), h(32), status (Power::standard)
{
	make_brick(1);
}

void Brick::make_brick(int lvl)
{
	// we want the % value to be slightly higher than the number of power
	// bricks - I want to find an automatic way to do this... TODO
	status = Power::generateStatus();
	Brick::doPowerUp(Power::make_all_normal);
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
	{
		return; // we don't draw broken bricks
	}

	if (w > 12 && h > 12) // check if the brick is big enough to shadow it
	{
		// render with shadow
		rectfill(bmp, x, y, x + w, y + h, makecol(static_cast<int>(c.r*0.6), static_cast<int>(c.g*0.6), static_cast<int>(c.b*0.6)));
		rectfill(bmp, x+3, y+3, x + w-3, y + h-3, makecol(static_cast<int>(c.r*0.8), static_cast<int>(c.g*0.8), static_cast<int>(c.b*0.8)));
		rectfill(bmp, x+6, y+6, x + w-6, y + h-6, makecol(c.r, c.g, c.b));
	}
	else
	{
		// render normal
		rectfill(bmp, x, y, x + w, y + h, makecol(c.r, c.g, c.b));
	}

}

/*!
	\brief most of these functions are not really needed - I'm only using it until I move over all relevent functionality to the brick class itself
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
	if (status != Power::unbreakable)
	{
		--life;
		fixColor();
	}
	else
	{
		std::cout << "We just hit an unbrekable" << std::endl;
	}
}

// See header file for what this function does
Power::brickStatus Brick::getUsableStatus()
{
	if (life <= 0)
	{
		//only give power when dead
		return status;
	}
	return Power::standard;
}

void Brick::doPowerUp(Power::brickStatus doWhat)
{
	switch (doWhat)
	{
		case Power::make_bricks_gray:
			fixColor();
			isGray=true;
			break;
		case Power::make_all_normal:
			fixColor();
			isGray = false;
			break;
		default:
			break;
	}
}

void Brick::fixColor()
{
	if (!isGray)
	{
		c.b = 0;
		c.g = 255 - ((life <= 10) ? life * 20 : 254);
		c.r = status * 100;
		/*! \bug sometime unbreakable bricks will still be white when all bricks go gray */
		if (status == Power::unbreakable)
		{
			//brick should be white (or really inverse of background).
			c.b = c.g = c.r = 255;
		}
	}
	else
	{
		c.r=204;
		c.g=204;
		c.b=204;

	}
}

void Brick::move(int x, int y)
{
	this->x = x;
	this->y = y;
}
