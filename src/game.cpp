#include "game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init_game()
{
	level = 1;
	lives = 5;

	game_field.do_new_random_level(1);
	restart_level();
}

void Game::restart_level()
{
	//This should actually be creating the /same/ level - but we will deal with this later
	game_field.do_new_random_level(1);

	//Now we continue because the level was just recreated
	continue_level();
}

void Game::continue_level()
{
	ball.init(); // init the ball

	ball.sticky_time = BPS_OF_TIMER_MANAGER * 3; // 3 secs before launch of ball =)
}

int Game::lost_life()
{
	if (! flag_cheat )
	{
		--lives;
	}
	else
	{
		std::cout << "We are cheating..." << std::endl;
	}
	std::cout << " " << lives << " at level " << level <<std::endl;
	if (lives <= 0)
	{
		textout_ex( screen, font, "Are you for real?", SCREEN_H / 2, SCREEN_W / 2, makecol( 255, 0, 0), makecol( 0, 0, 0));
		controls::waitUntilEvent();
		init_game(); //do we really want to call this here? Should the kernel do this?
		return GAME_UDP_LOST_GAME;
		// we need to have a better method of restarting game vs continuing level
	}
	else
	{
		textout_ex( screen, font, "You lost!!", SCREEN_H / 2, SCREEN_W / 2, makecol( 255, 0, 0), makecol( 0, 0, 0));
		controls::waitUntilEvent();
	}
	return KERNEL_UDP_OK;
}


void Game::next_level()
{
	++level;
}

void Game::prev_level()
{
	level = std::max(level - 1, 1);
}
