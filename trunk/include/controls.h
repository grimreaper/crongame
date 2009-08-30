/* \brief handles keyboard, mouse, and joystick? input
	This class contains a series of functions that return true or false
	based on if certain controls are pressed or not pressed. This allowed for future user config controls
	as well as mouse+ketboard+joystick controls.
*/
#ifndef CONTROL_H
#define CONTROL_H

#include "common.h"

class controls
{
	public:
		controls();
		static bool release_ball_from_paddle();
		static bool pause_game();
		static bool quit_game();
		static bool cheat_add_level();
		static bool cheat_rm_level();
		//Did anything happpen - joystick, mouse, or keyboard!?
		static bool event();

		// returns the new x that the paddle should be on
		static int getNewPaddleX(int paddle_x, int paddle_w);

		// Loop until and event happens
		static void waitUntilEvent();
	private:
		static int kbspeed;

		// movment related functions
		static int goLeft();
		static int goRight();
		static int goMouse(int paddle_w);
};

#endif
