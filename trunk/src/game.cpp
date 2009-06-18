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
}

void Game::next_level()
{
	++level;
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
	std::cout << "we have " << lives << " at level " << level <<std::endl;
	if (lives <= 0)
	{
		textout_ex( screen, font, "Are you for real?", SCREEN_H / 2, SCREEN_W / 2, makecol( 255, 0, 0), makecol( 0, 0, 0));
		clear_keybuf();
		readkey();
		init_game();
		return GAME_UDP_LOST_GAME;
		// we need to have a better method of restarting game vs continuing level
	}
	else
	{
		textout_ex( screen, font, "You lost!!", SCREEN_H / 2, SCREEN_W / 2, makecol( 255, 0, 0), makecol( 0, 0, 0));
	}
	return KERNEL_UDP_OK;
}
