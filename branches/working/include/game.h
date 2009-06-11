#ifndef GAME_H
#define GAME_H
class Game
{
	public:
		Game();
		~Game();

		//start a completely new game
		void init_game();
		//restart level - from the top
		void restart_level();
		//continue level - returns ball and such to starting
		//position - but not the field.
		void continue_level();

		int lives;
		int level;

	private:

};
#endif
