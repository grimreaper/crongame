#ifndef GAME_H
#define GAME_H
#include "common.h"
class Game
{
	public:
		Game();
		~Game();

		void init_game();

		int lives;
		int level;

		log *logger;
	private:

};
#endif
