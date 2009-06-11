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

	game_field.do_new_random_level(3,2,1); // create a level

	show_mouse(NULL); // hide mouse

	// This is the main loop of the game, were all the action actually happens
	while (ret != KERNEL_UDP_EXIT && ret != KERNEL_UDP_QUIT) // DEBUG , ESC key should be enabled ??? maybe... maybe not
	{
		if (speed_counter > 0) // while we still have logic frames to do
		{
			ret = update(); // update game logic and see which state we are

			if (ret == KERNEL_UDP_LOST_LIFE) // lost a life!
			{
				textout_ex( screen, font, "You lost!!", SCREEN_H / 2, SCREEN_W / 2, makecol( 255, 0, 0), makecol( 0, 0, 0));
				--lives;
				if (lives == 0)
				{
					textout_ex( screen, font, "For real!", SCREEN_H / 2 + 30, SCREEN_W / 2, makecol( 255, 0, 0), makecol( 0, 0, 0));
					mygame.init_game();
					// we need to have a better method of restarting game vs continuing level
				}

				//textout_ex( screen, font, (char)lives, SCREEN_H / 2 + 30, SCREEN_W / 2, makecol( 255, 0, 0), makecol( 0, 0, 0));
				clear_keybuf();
				readkey();
				init_game(); // DEBUG - we should show a message and take down a life
			}

			if (ret == KERNEL_UDP_NEXT_LEVEL || key[KEY_SPACE]) // DEBUG -- REMOVE THE CHEAT, the KEY_SPACE thing!!
			{
				textout_ex( screen, font, "Next level!!", SCREEN_H / 2, SCREEN_W / 2, makecol( 255, 0, 0), makecol( 0, 0, 0));

				mygame.next_level();

				// pick new level parameters
				//don't let lives of bricks go greater than 5
				int l = std::min(mygame.level, 5);
				int w = 3 + rand() % mygame.level + mygame.level;
				int h = 3 + rand() % mygame.level;
				if (w > GAMEFIELD_MAX_W-2)
				{
					w = GAMEFIELD_MAX_W-2; // oh the guy can play :o
				}
				if (h > GAMEFIELD_MAX_H-2)
				{
					h = GAMEFIELD_MAX_H-2; // oh the guy can play :o
				}

				game_field.do_new_random_level(w,h,l); // new level
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

	if (ball.update(paddle, game_field))
	{
		ret = KERNEL_UDP_LOST_LIFE; // player lost life :(
	}

	if (game_field.update())
	{
		ret = KERNEL_UDP_NEXT_LEVEL; // gamefield clear, go to next level \\o o//
	}

	if (key[KEY_ESC]) // exit game -- DEBUG , WE MUST CONFIRM THIS!!
	{
		ret = KERNEL_UDP_EXIT;
	}

	/*
	I think we have an issue with the FPS counter or some other threads.
	pausing stops the screen - but not the game.
	// pause the game.
	if (key[KEY_P])
	{
		clear_keybuf();
		while (!key[KEY_Q])
		{
			readkey();
		}
	}
	*/

	return ret;
}

// render game
void Kernel::render()
{
	clear_bitmap(double_buffer); // debug - here we should/could blit the background

	// first, everything gets drawed to the double buffer bitmap
	game_field.render(double_buffer); // render the game field (the bricks)
	paddle.render(double_buffer); // render the paddle
	ball.render(double_buffer); // render the ball

	// after that, we blit (draw) the double buffer to screen
	blit(double_buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
}


// Kernel::init_game()
// this inits the game without reseting the kernel or the level
// is used for when you start a game , lose a life, etc
void Kernel::init_game()
{
	mygame.init_game();

	paddle.init(); // init the paddle

	ball.init(); // init the ball

	ball.sticky_time = BPS_OF_TIMER_MANAGER * 3; // 3 secs before launch of ball =)

	position_mouse((int)paddle.x , (int)paddle.y ); // put the mouse cursor in paddle

	clear_keybuf();	 // clear keyboard buffer


}
