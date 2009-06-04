#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdarg.h>

class log
{
	public:
		log();
		enum colors
		{
			NORMAL = 0
		};
		void msg(int lvl, std::string str, ...);

		int level;
};
#endif
