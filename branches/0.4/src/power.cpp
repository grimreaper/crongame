#include "power.h"

Power::brickStatus Power::generateStatus()
{
	// we want the % value to be slightly higher than the number of power
	// bricks - I want to find an automatic way to do this... TODO

	int tmpRand = arc4rand() % 16 + 1;
	#ifdef BRICK_NUM
		tmpRand = BRICK_NUM;
		std::cout << " We just cheated ";
	#endif
	std::cout << "We just created a brick with power # " << tmpRand << std::endl;
	switch (tmpRand)
	{
		case 1:
			return make_all_normal;

		case 2:
			return make_ball_fire;

		case 3:
			return add_live;

		case 4:
			return make_ball_big;

		case 5:
			return make_ball_small;

		case 6:
			return no_see_paddle;

		case 7:
			return make_paddle_small;

		case 8:
			return make_paddle_big;

		case 9:
			return make_paddle_zero;

		case 10:
			return make_paddle_giant;
		case 11:
			return unbreakable;
		case 12:
			return make_ball_fast;
		case 13:
			return make_ball_slow;
		case 14:
			return make_bricks_gray;
		default:
			return standard;
	}
}
