#ifndef POWER_H
#define POWER_H
#include "common.h"
#include "krandom.h"

/*!
 * \class Power
 * \brief Handles generating powers ups. Does not execute them.
 * \author Eitan Adler
 * \todo Must provide method of non-even distribution of powers
 * \enum brickStatus Contains the values for all valid brick powers
 * \relatesalso brick.doPowerUp() padel.doPowerUp() game.doPowerUp()
 *
 * \details Contains the enum to which powers are mapped; includes function to randomly choose powerup.
 * 
*/

class Power
{
	public:
		enum brickStatus
		{
			standard, /*!< Just a regular brick*/
			make_all_normal, /*!< remove all active powers */
			make_ball_fire,
			add_live, //yes I am aware that this is not proper English - I am using lives and lifes differently
			make_ball_big,
			make_ball_small,
			no_see_paddle,
			make_paddle_small,
			make_paddle_big,
			make_paddle_zero,
			make_paddle_giant,
			unbreakable,
			make_ball_fast,
			make_ball_slow
		};

		static brickStatus generateStatus();
	private:
};
#endif
