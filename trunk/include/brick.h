#ifndef BRICK_H
#define BRICK_H

#include <allegro.h>

class Brick
{
	public:
		// Operations
		Brick();
		~Brick();

		void update();
		void render(BITMAP * bmp);

		// Attributes
		int life; // life, in ball hits

		int x; // position, in pixels
		int y;

		int w; // size, in pixels
		int h;

		RGB c; // color, in R,G,B
};

#endif
