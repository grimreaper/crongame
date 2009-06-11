#ifndef GERROR_C
#define GERROR_C

#include "gerror.h"

/*
Goes back to text mode, shows the message and ends the program.
Has printf like format for msg.
*/
void raise_error(AL_CONST char *msg, ...)
{
	char *buf;
	/* exits the graphics mode */
	set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);

	/* creates the buffer */
	buf = (char *)malloc(4096);

	if (buf == NULL)
	{
		allegro_message("raise_error(): There is a error, and I'm out of virtual memory to show the error message. :^(\n");
	}
	else
	{
		/* parse the variable parameters */
		va_list ap;
		va_start(ap, msg);
		uvszprintf(buf, 4096, msg, ap);
		va_end(ap);

		allegro_message("%s\n", buf);
		free(buf);
	}

	exit(EXIT_FAILURE); /* abort the program */
}

#endif

#ifdef TEST
	int main (void)
	{
		/* test that we actually exit when we call the function - if there is anything else to test - add it here */
		atexit(exiting);
		allegro_init();
		raise_error("testing");
		return 0;
	}

	void exiting()
	{
		std::cout << "exit ok" << std::endl;
	}
#endif
