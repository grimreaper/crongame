#include "merror.h"
#include <kernel.h>

Kernel::Kernel() : double_buffer (NULL)
{
}

Kernel::Kernel(const Kernel&) : double_buffer (NULL) {}
//Kernel Kernel::operator=(const Kernel& newKernel) { return this; }


void Kernel::init()
{
	double_buffer = create_bitmap(SCREEN_W,SCREEN_H);
	if (!double_buffer)
	{
		raise_error("Kernel::init() - can't create double buffer!");
	}
	clear_bitmap(double_buffer);
}

void Kernel::shutdown()
{
	if (double_buffer)
	{
		destroy_bitmap(double_buffer);
	}
      double_buffer = NULL;
}

Kernel::~Kernel()
{
	shutdown(); // we shutdown on delete :)
}


void Kernel::play()
{

	int ret = KERNEL_UDP_OK; // current game state, all OK
	int level = 1 ; // current level of the game


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
			std::cout << "just called kernel update " <<std::endl;

			if (ret == KERNEL_UDP_LOST_LIFE) // lost a life!
			{
				textout_ex( screen, font, "You lost!!", SCREEN_H / 2, SCREEN_W / 2, makecol( 255, 0, 0), makecol( 0, 0, 0));
				readkey();
				init_game();
			}

			if (ret == KERNEL_UDP_NEXT_LEVEL || key[KEY_SPACE]) // DEBUG -- REMOVE THE CHEAT, the KEY_SPACE thing!!
			{
				// next level
				textout_ex( screen, font, "You won!!", SCREEN_H / 2, SCREEN_W / 2, makecol( 255, 0, 0), makecol( 0, 0, 0));
				readkey();

				--level; // next level :)

				// pick new level parameters
				int l = level;
				std::cout << "l is " << l << " ";
				int w = 3 + arc4random() % level + level;
				std::cout << "w is " << w << " ";
				int h = 3 + arc4random() % level ;
				std::cout << "h is " << h << " ";

				if (level > 5)
				{
					std::cout << "l > 5 ";

					l = 5; // max life of bricks
				}
				if (w > GAMEFIELD_MAX_W-2)
				{
					std::cout << "w > GAMEFIELD_MAX_W-2 ";

					w = GAMEFIELD_MAX_W-2; // oh the guy can play :o
				}
				if (h > GAMEFIELD_MAX_H-2)
				{
					std::cout << "h > GAMEFIELD_MAX_H-2 ";

					h = GAMEFIELD_MAX_H-2; // oh the guy can play :o
				}

				std::cout << "about to start new game from the gamefield";
				game_field.do_new_random_level(w,h,l); // new level
				std::cout << "about to start init game ";
				std::cout << std::endl;
				init_game();
			}

			std::cout << "speed down" << std::endl;
			--speed_counter; // decrease logic frames to do
		}
		else
		{
			std::cout << "render" << std::endl;
			render(); // draw the game
			fps_counter++; // count frames per second (FPS) (check mtimer.cpp, this aren't the real FPS, fps_real has the real FPS
		}
	}

	std::cout << "clear key buffer" << std::endl;
	clear_keybuf();
	_stop_global_timer(); // stop the global timer
	std::cout << "reset to 0" << std::endl;
	time_counter = speed_counter = fps_counter = fps_real = 0; // leave everything nice, just to be sure

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

// update game logic
int Kernel::update()
{
	int ret = KERNEL_UDP_OK; // by default, everything is OK

	paddle.update(); // update the paddle logic

	if (ball.update(paddle, game_field))
	{
		ret = KERNEL_UDP_LOST_LIFE; // player lost life :(
	}
	std::cout << " about to update GF" << std::endl;

	if (game_field.update())
	{
		ret = KERNEL_UDP_NEXT_LEVEL; // gamefield clear, go to next level \\o o//
	}
	std::cout << " done with update GF" << std::endl;


	if (key[KEY_ESC]) // exit game -- DEBUG , WE MUST CONFIRM THIS!!
	{
		ret = KERNEL_UDP_EXIT;
	}

      return ret;
}

// Kernel::init_game()
// this inits the game without reseting the kernel or the level
// is used for when you start a game , lose a life, etc
void Kernel::init_game()
{
	std::cout << "kernel is initing ";

	paddle.init(); // init the paddle
	std::cout << "paddle is done ";

	ball.init(); // init the ball 
	std::cout << "ball is done ";

	ball.sticky_time = BPS_OF_TIMER_MANAGER * 3; // 3 secs before launch of ball =)

	position_mouse((int)paddle.x , (int)paddle.y ); // put the mouse cursor in paddle

	clear_keybuf();    // clear keyboard buffer
}

