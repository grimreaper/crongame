#ifndef GERROR_H
#define GERROR_H
/*! \file gerror.h
\brief Error message system.
*/

#include "common.h"

/*! Goes back to text mode, shows the message and ends the program. Printf style. */
void raise_error(AL_CONST char *msg, ...); 

#ifdef TEST
	#include <iostream>
	void exiting();
#endif

#endif
