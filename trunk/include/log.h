#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>

class log
{
	public:
		enum colors
		{
			NORMAL = 0
		};
		int msg(colors color, int lvl, char *msg, ...);
	private:
		
};
#endif
