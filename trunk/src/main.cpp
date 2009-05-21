#define ARC4RANDOM_MAX      0x100000000
#include <allegro.h>
#include "kernel.h"
#include "merror.h"

int main (void)
{
	int vid_m = GFX_AUTODETECT;
	int vid_w = 640;
	int vid_h = 480;

	int depth = 32;

	if (allegro_init() != 0)
	{
		raise_error("main() : Allegro failed to start!");
	}

	if (install_timer() != 0)
	{
		raise_error("main() : can't install timer driver!");
	}

	if (install_keyboard() != 0)
	{
		raise_error("main() : can't install keyboard driver!");
	}

	if (install_mouse() <= 0)
	{
		raise_error("main() : can't install mouse driver! a mouse is needed to play this game! sorry...");
	}

	set_color_depth(depth);

	// init video mode, trying many configurations to see if we can use anyone
	if ( set_gfx_mode(vid_m, vid_w, vid_h, 0, 0) != 0)
	{
		set_color_depth(16);
		if ( set_gfx_mode(vid_m, vid_w, vid_h, 0, 0) != 0)
		{
			set_color_depth(15);
			if ( set_gfx_mode(vid_m, vid_w, vid_h, 0, 0) != 0)
			{
				set_color_depth(32);
				if ( set_gfx_mode(vid_m, vid_w, vid_h, 0, 0) != 0)
				{
					set_color_depth(24);
					if ( set_gfx_mode(vid_m, vid_w, vid_h, 0, 0) != 0)
					{
						raise_error("main() : I can't set the graphics mode (%3d x %3d @ %2d bpp)\nI also tried with 16 bpp, 15 bpp, 32 bpp and 24 bpp\n", vid_w, vid_h, depth);
					}
				}
			}
		}
	}

	set_color_conversion(COLORCONV_TOTAL | COLORCONV_KEEP_TRANS);
	set_window_title("Kronoide");

	Kernel *kernel;
	kernel = new Kernel;
	//initialize and play game here
	kernel->init();
	kernel->play();
	kernel->shutdown();
	delete kernel;

	allegro_exit();
	return 0;
}
END_OF_MAIN();