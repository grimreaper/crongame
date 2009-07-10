#include "controls.h"

bool controls::release_ball_from_paddle()
{
	/* If the left button is pressed or or if the space bar is pressed. */
	return ((mouse_b & 1) || key[KEY_SPACE]);
}

bool controls::pause_game()
{
	return key[KEY_P];
}

bool controls::quit_game()
{
	return key[KEY_ESC];
}
