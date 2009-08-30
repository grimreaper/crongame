#include "controls.h"

extern int controls::kbspeed;
extern int flag_use_mouse;

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

// returns the new X of the paddle;
//PRIVATE
int controls::goMouse(int paddle_w)
{
      return mouse_x - (paddle_w / 2);
}

// returns how far right the paddle should go
//RPIVATE
int controls::goRight()
{
	if (key[KEY_RIGHT])
	{
		kbspeed++;
		return kbspeed;
	}
	// if we press and hold get faster and faster - otherwise reset to 0 each time.
	kbspeed = 0;
	return 0;
}

// returns how far left the paddle should go.
// PRIVATE
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

// returns the correct X the paddle should be at
// only the controls class should know if we are using the mouse;
// move the flag to a control class private member.
// PUBLIC
int controls::getNewPaddleX(int paddle_x, int paddle_w)
{
	int new_x = paddle_x;
	if (flag_use_mouse == TRUE)
	{
		new_x = goMouse(paddle_w);
	}
	else
	{
		new_x += controls::goRight();
		new_x -= controls::goLeft();
	}
	return new_x;
}
