#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdarg.h>

#ifndef COMPILE_LOG_LEVEL
	#define COMPILE_LOG_LEVEL 10
#endif

class log
{
	public:
		log();
		void msg(int lvl, std::string str, ...);
		void msg(std::string str, ...);

		int level;
};
#endif
