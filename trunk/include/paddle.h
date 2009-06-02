#ifndef PADDLE_H
#define PADDLE_H

#include <allegro.h>

class Paddle
{
	public:
		// Operations
		Paddle();
		~Paddle();
		void init();
		void update();
		void render(BITMAP * bmp);
		void reset_color();

		// Attributes
		float x;
		float y;
		int w;
		int h;
		RGB c;
};

#endif
