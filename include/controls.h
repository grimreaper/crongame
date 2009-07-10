/*
	This class contains a series of functions that return true or false
	based on if certain controls are pressed or not pressed. This allowed for future user config controls
	as well as mouse+ketboard+joystick controls.
*/
#ifndef CONTROL_H
#define CONTROL_H

#include <allegro.h>


class controls
{
	public:
		static bool release_ball_from_paddle();
		static bool pause_game();
		static bool quit_game();
};

#endif
