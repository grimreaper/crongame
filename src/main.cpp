#include <allegro.h>
#include <string.h>
#include <stdio.h>

#include "gerror.h"
#include "kernel.h"

int main( int argc, char *argv[])
{
	// parameters config
	int depth = -1;

	int vid_m = GFX_AUTODETECT;

	int vid_w = 640;

	int vid_h = 480;

	bool want_sound = true;

	// check command line parameters
	for (int i = 1; i < argc; ++i)
	{
		if (!stricmp(argv[i], "-wn") ||
			!stricmp(argv[i], "-w") ||
			!stricmp(argv[i], "-win") ||
			!stricmp(argv[i], "-windowed"))
		{
			vid_m = GFX_AUTODETECT_WINDOWED;
		}


		if (!stricmp(argv[i], "-nosound") ||
			!stricmp(argv[i], "-silent") ||
			!stricmp(argv[i], "-ns"))
		{
			want_sound = false;
		}

		if (!stricmp(argv[i], "-bpp16"))
		{
			depth = 16;
		}

		if (!stricmp(argv[i], "-bpp15"))
		{
			depth = 15;
		}

		if (!stricmp(argv[i], "-bpp32"))
		{
			depth = 32;
		}

		if (!stricmp(argv[i], "-bpp24"))
		{
			depth = 24;
		}

		if (!stricmp(argv[i], "-bpp8"))
		{
			raise_error("main() : Sorry, this program don't support 8 bpp displays.\nThis program needs a true color display at %3d x %3d resolution.\nTip: Try removing the -bpp8 switch from the command line invocation.", vid_w, vid_h);
		}

	}


	if (allegro_init())
	{
		raise_error("main() : Allegro failed to start!");
	}

	if (install_timer())
	{
		raise_error("main() : can't install timer driver!");
	}

	if (install_keyboard())
	{
		raise_error("main() : can't install keyboard driver!");
	}

	if (install_mouse() < 0)
	{
		raise_error("main() : can't install mouse driver! a mouse is needed to play this game! sorry...");
	}

	if (depth < 16)
	{
		depth = desktop_color_depth(); // get desktop color depth
	}

	// safe check
	depth = std::max(16, depth);

	set_color_depth(depth);

	// init video mode, trying many configurations to see if we can use anyone
	if ( set_gfx_mode(vid_m, vid_w, vid_h, 0, 0) )
	{
		set_color_depth(16);

		if ( set_gfx_mode(vid_m, vid_w, vid_h, 0, 0) )
		{
			set_color_depth(15);

			if ( set_gfx_mode(vid_m, vid_w, vid_h, 0, 0) )
			{
				set_color_depth(32);

				if ( set_gfx_mode(vid_m, vid_w, vid_h, 0, 0) )
				{
					set_color_depth(24);

					if ( set_gfx_mode(vid_m, vid_w, vid_h, 0, 0) )
					{
						raise_error("main() : I can't set the graphics mode (%3d x %3d @ %2d bpp)\nI also tried with 16 bpp, 15 bpp, 32 bpp and 24 bpp\n", vid_w, vid_h, depth);
					}
				}
			}
		}
	}

	set_color_conversion(COLORCONV_TOTAL | COLORCONV_KEEP_TRANS);

	// sound
	if (want_sound)
	{
		reserve_voices(8, 0);
		set_volume_per_voice(2);
		install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
		set_volume(255, -1);
	}

	set_window_title("Crontab!");

	// run game
	Kernel *kernel	;
	kernel = new(Kernel);
	kernel->init();
	kernel->play();
	kernel->shutdown();
	delete(kernel);

	allegro_exit();

	return 0;
}
END_OF_MAIN();
