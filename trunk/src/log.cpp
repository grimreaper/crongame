#include <log.h>

int msg(colors color, int lvl, char *msg, ...)
{
}
/*
      char *buf;

      /* creates the buffer */
/*
      buf = (char *)malloc(4096);

      if (buf == NULL)
      {
            std::cout << "log: There is a error, and I'm out of virtual memory to show the error message. :^(\n" << std::endl;
      }
      else
      {
            // parse the variable parameters
            va_list ap;
            va_start(ap, msg);
            uvszprintf(buf, 4096, msg, ap);
            va_end(ap);

            std::cout << buf << std::endl;
            free(buf);
      }
}
*/

#ifdef TEST
int main (void)
{
	log logger = log();
	return 0;
}
#endif
