#include "kernel.h"

Kernel::Kernel() : double_buffer (NULL)
{
}

Kernel::~Kernel()
{
	shutdown(); // we shutdown on delete :)
}


void Kernel::init()
{
	mygame = Game();
	mygame.init_game();
	double_buffer = create_bitmap(SCREEN_W,SCREEN_H);
	if (!double_buffer)
	{
		raise_error("Kernel::init() - can't create double buffer!");
	}
	clear_bitmap(double_buffer);

}

void Kernel::play()
{
	int ret = KERNEL_UDP_OK; // current game state, all OK

	_start_global_timer(); // we start a global timer, check mtimer.cpp

	time_counter = speed_counter = fps_counter = fps_real = 0; // we reset the global timer parameters

	clear_keybuf();

	init_game(); // initialize a game run

	show_mouse(NULL); // hide mouse

	// This is the main loop of the game, were all the action actually happens
	while (ret != KERNEL_UDP_EXIT && ret != KERNEL_UDP_QUIT) // DEBUG , ESC key should be enabled ??? maybe... maybe not
	{
		if (speed_counter > 0) // while we still have logic frames to do
		{
			ret = update(); // update game logic and see which state we are

			if (ret == GAME_UDP_LOST_LIFE) // lost a life!
			{
				ret = mygame.lost_life();
				init_game();
			}

			if (controls::cheat_rm_level())
			{
				mygame.prev_level();
				mygame.game_field.do_new_random_level(mygame.level); // new level
				init_game();
			}

			if (ret == GAME_UDP_NEXT_LEVEL || ret == GAME_UDP_LOST_GAME || controls::cheat_add_level() ) // DEBUG -- REMOVE THE CHEAT, the KEY_SPACE thing!!
			{

				if (ret != GAME_UDP_LOST_GAME)
				{
					textout_ex( screen, font, "Next level!!", SCREEN_H / 2, SCREEN_W / 2, makecol( 255, 0, 0), makecol( 0, 0, 0));
					mygame.next_level();
				}

				mygame.game_field.do_new_random_level(mygame.level); // new level
				init_game();
			}

			--speed_counter; // decrease logic frames to do
		}
		else
		{
			render(); // draw the game
			++fps_counter; // count frames per second (FPS) (check mtimer.cpp, this aren't the real FPS, fps_real has the real FPS
		}
	}

	clear_keybuf();
	_stop_global_timer(); // stop the global timer
	time_counter = speed_counter = fps_counter = fps_real = 0; // leave everything nice, just to be sure
}

void Kernel::shutdown()
{
	if (double_buffer)
	{
		destroy_bitmap(double_buffer);
	}
	double_buffer = NULL;
}

// -- class private stuff from here --

// update game logic
int Kernel::update()
{
	int ret = KERNEL_UDP_OK; // by default, everything is OK

	paddle.update(); // update the paddle logic

	if (mygame.ball.update(paddle, mygame.game_field))
	{
		ret = GAME_UDP_LOST_LIFE; // player lost life :(
	}

	if (mygame.game_field.update())
	{
		ret = GAME_UDP_NEXT_LEVEL; // gamefield clear, go to next level \\o o//
	}

	if (controls::quit_game()) // exit game -- DEBUG , WE MUST CONFIRM THIS!!
	{
		ret = KERNEL_UDP_EXIT;
	}

	/*
	I think we have an issue with the FPS counter or some other threads.
	pausing stops the screen - but not the mygame.
	*/
	// pause the mygame.
	if (controls::pause_game())
	{
		clear_keybuf();
		while (!controls::release_ball_from_paddle())
		{
			_stop_global_timer(); // stop the global timer
			readkey();
			_start_global_timer(); // we start a global timer, check mtimer.cpp
		}
	}

	return ret;
}

// render game
void Kernel::render()
{
	clear_bitmap(double_buffer); // debug - here we should/could blit the background

	// first, everything gets drawed to the double buffer bitmap
	mygame.game_field.render(double_buffer); // render the game field (the bricks)
	paddle.render(double_buffer); // render the paddle
	mygame.ball.render(double_buffer); // render the ball

	// after that, we blit (draw) the double buffer to screen
	blit(double_buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
}


// Kernel::init_game()
// this inits the game without reseting the kernel or the level
// is used for when you start a game , lose a life, etc
void Kernel::init_game()
{
	mygame.restart_level();

	paddle.init(); // init the paddle

	position_mouse((int)paddle.x , (int)paddle.y ); // put the mouse cursor in paddle

	clear_keybuf();	 // clear keyboard buffer


}

void Kernel::restart_game()
{
	mygame.init_game();
	init_game();
}
