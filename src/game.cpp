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
