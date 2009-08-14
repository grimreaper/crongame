#ifndef GAME_H
#define GAME_H

#include "common.h"
#include "gerror.h"
#include "game_status_constants.h"
#include "ball.h"
#include "paddle.h"
#include "dialog.h"
#include "gamefield.h"
#include "mtimer.h" //For the timer constants

extern int flag_cheat;

/*! \class Game
 * \brief This is where things happen. 
*/

class Game
{
	public:
		Game();
		~Game();

		/*! \brief start a completely new game */
		void init_game();
		/*! \brief restart level - from the top */
		void restart_level();
		/*! \brief continue level 
		 * returns ball and such to starting position - but not the field.
		*/
		void continue_level();

		/*! \brief we move on to the next level */
		void next_level();
		/*! \brief or we just move back */
		void prev_level();

		/*! \brief we just lost a life */
		int lost_life();

		/*! \var Contains the number of lives the user has left */
		int lives;
		/*! \var What level are we showing the user */
		int level;

 		/*! \var The game ball
		 * \todo when we allow multiple balls this method of storing balls has to change.
		*/
		Ball ball;
		GameField game_field; /*! \var the game field */
		Paddle paddle; /*! \var the player paddle */

		void update(); /*! \brief calls the update method on all the relevent children */
		void render(BITMAP *double_buffer); /*! \brief calls the render method on all of the relevent children */

	private:

};
#endif
