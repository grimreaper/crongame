#ifndef POWER_H
#define POWER_H

#include "krandom.h"
#include <iostream>

class power
{
	public:
		enum brickStatus
		{
			standard,
			make_all_normal,
			make_ball_fire,
			add_live, //yes I am aware that this is not proper English - I am using lives and lifes differently
			make_ball_big,
			make_ball_small,
			no_see_paddle,
			make_paddle_small,
			make_paddle_big,
			make_paddle_zero,
			make_paddle_giant,
			unbreakable,
			make_ball_fast,
			make_ball_slow
		};

		static brickStatus generateStatus();
	private:
};
#endif
