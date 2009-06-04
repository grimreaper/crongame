#include <log.h>

log::log(): level (10)
{}

void log::msg(int lvl, std::string str, ...)
{
	if (lvl < level)
	{
		va_list ap;
		va_start (ap, str);
		vfprintf (stdout, str.c_str(), ap);
		printf("\n");
		va_end (ap);
	}
}


#ifdef TEST
int main (void)
{
	log logger = log();
	logger.msg(0,"Test");
	logger.msg(0,"Test 2\n");
	logger.msg(0,"Test %s", "3");
	logger.msg(0,"Test %d", 4);
	logger.msg(logger.level + 1,"you should never see this");
	return 0;
}
#endif
