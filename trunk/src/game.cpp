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
	textout_ex( screen, font, "You lost!!", SCREEN_H / 2, SCREEN_W / 2, makecol( 255, 0, 0), makecol( 0, 0, 0));
	--lives;
	if (lives <= 0)
	{
		textout_ex( screen, font, "For real!!", SCREEN_H / 2 + 30, SCREEN_W / 2, makecol( 255, 0, 0), makecol( 0, 0, 0));
		clear_keybuf();
		readkey();
		init_game();
		return GAME_UDP_NEXT_LEVEL;
		// we need to have a better method of restarting game vs continuing level
	}
	return KERNEL_UDP_OK;
}
