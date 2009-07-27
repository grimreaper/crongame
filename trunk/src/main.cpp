#include <allegro.h>
#include <adime.h>
#include <iostream>
#include <getopt.h>

#include "gerror.h"
#include "kernel.h"
//#include "dialog.h"

int flag_windowed = FALSE;
int flag_cheat = FALSE;

int want_sound = TRUE;
int depth = -1;
/*
char player_name[256] ="";
int update_hs = 0;
*/
static struct option long_options[] =
{
	{"windowed", no_argument, &flag_windowed, TRUE},
	{"wn", no_argument, &flag_windowed, TRUE},
	{"win", no_argument, &flag_windowed, TRUE},
	{"bpp", required_argument, &depth, 'b'},
	{"silent", no_argument, &want_sound, FALSE},
	{"nosound", no_argument, &want_sound, FALSE},
	{"ns", no_argument, &want_sound, FALSE},
	{"cheat", no_argument, &flag_cheat, TRUE},
	{NULL, 0, NULL, 0}
};

int main( int argc, char *argv[])
{
	// parameters config
	int vid_w = 640;

	int vid_h = 480;

	if (allegro_init())
	{
		std::cout << "main() : Allegro failed to start!" << std::endl;
		exit(1);
	}

	int c = 0;
	int option_index = 0;

	while ((c = getopt_long (argc, argv, "bw", long_options, &option_index)) != -1)
	{
		switch (c)
		{
			case 'b':
				depth = (int)optarg;
				break;
			case 'w':
				flag_windowed = TRUE;
				break;
			default:
				break;
		}
	}

	while (optind < argc)
	{
		std::cout << "non-option argument" << argv[optind++] << std::endl;
	}

	int vid_m = GFX_AUTODETECT;
	if (flag_windowed)
	{
		vid_m = GFX_AUTODETECT_WINDOWED;
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

	/*
	if (adime_init() != 0)
	{
		std::cout << "main() : Adime failed to start!" << std::endl;
		exit(1);
	}
	clear(screen);
	ask_player_name();
	*/
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
END_OF_MAIN()
