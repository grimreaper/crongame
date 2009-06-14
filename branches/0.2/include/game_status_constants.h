#ifndef GAME_STATUS_CONST_H
#define GAME_STATUS_CONST_H

// some states of the update of the game (this is NOT bitmask values)

// all fine
const int KERNEL_UDP_OK = 0;

// go to next level
const int GAME_UDP_NEXT_LEVEL = 1;

// lost a life
const int GAME_UDP_LOST_LIFE = 2;

//lost the game
const int GAME_UDP_LOST_GAME = 3;

// pause
const int KERNEL_UDP_PAUSE = 100;

// exit from game (to menu)
const int KERNEL_UDP_EXIT = 101;

// exit to operating system (DOS ? :P)
const int KERNEL_UDP_QUIT = 102;
#endif
