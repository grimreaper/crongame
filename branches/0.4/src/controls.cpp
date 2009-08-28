#include "controls.h"

extern int controls::kbspeed;

controls::controls()
{
	kbspeed = 0;
}
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

bool controls::cheat_add_level()
{
	return key[KEY_PLUS_PAD];
}

bool controls::cheat_rm_level()
{
	return key[KEY_MINUS_PAD];
}

bool controls::event()
{
	return (mouse_b || keypressed());
}

void controls::waitUntilEvent()
{
	while (!event()) {}
	clear_keybuf();
	mouse_b=0;
}

int controls::goMouse(int paddle_w)
{
      return mouse_x - (paddle_w / 2);
}

int controls::goRight()
{
	if (key[KEY_RIGHT])
	{
		kbspeed++;
		return kbspeed;
	}
	kbspeed = 0;
	return 0;
}

int controls::goLeft()
{
	if (key[KEY_LEFT])
	{
		kbspeed++;
		return kbspeed;
	}
	kbspeed = 0;
	return 0;
}
