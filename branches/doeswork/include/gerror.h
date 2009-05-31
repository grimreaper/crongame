/*
-----------------------------------------------
Generic Allegro Project Template
By Kronoman - July 2003
Copyright (c) 2003, Kronoman
In loving memory of my father
-----------------------------------------------
-----------------------------------------------
Error messages
----------------------------------------------- 
*/
#ifndef GERROR_H
#define GERROR_H
/*! \file gerror.h
Error message system. 
*/

#include <allegro.h> // I use some stuff from here too, mainly, unicode strings ;)
#include <stdarg.h> // for the variable argument list
#include <stdlib.h> // for use of malloc 

/// Goes back to text mode, shows the message and ends the program. Printf style.
void raise_error(AL_CONST char *msg, ...); 

#endif
