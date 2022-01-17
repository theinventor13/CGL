#include <SDL.h>
#include <SDL_image.h>
#include <SDL_audio.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#define pi M_PI
#define cgl_max_window_count 100
#define cgl_arg_count(...) _cgl_arg_count(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define _cgl_arg_count(a, b, c, d, e, f, g, h, i, j, count, ...) count
#define cgl_first_arg(n, ...) n	

#include "cgl_render.h"
#include "cgl_graphics.h"
#include "cgl_image.h"
#include "cgl_input.h"
#include "cgl_text.h"
#include "cgl_events.h"
#include "cgl_audio.h"										



#define screen(x, y)						{init();                                                 \
											defaultfont()                                            \
											screenwidth = x;                                         \
											screenheight = y;                                        \
											cgl_default_window = cgl_makewindow(x, y, "CGL", false);}
											

#define quit()								{SDL_DestroyRenderer(cgl_default_window.renderer_handle);\
											SDL_DestroyWindow(cgl_default_window.window_handle);     \
											SDL_Quit();}

#define pause(ms)							SDL_Delay(ms);

#define cgl(x, y)							{screen(x, y);       \
											srand(time(0));      \
											while(!cgl_update()) \
												graphics();      \
											quit();}
		
#define cgl_print_error(string, ...) cgl_error(false, true, string, __VA_ARGS__)			
#define cgl_log_error(string, ...) cgl_error(true, false, string, __VA_ARGS__)
#define cgl_lap_error(string, ...) cgl_error(true, true, string, __VA_ARGS__)
//void cgl_log_error()
//void cgl_lap_error()

FILE * cgl_logfile_handle;
char cgl_default_logfile[200] = "cgl_log.txt";

//add logfile timestamps to name

void cgl_init_log(const char * filename){
	
	cgl_logfile_handle = fopen(filename, "w+");
	return;
	
}

void cgl_error(bool log, bool print, const char * string, ...){
	
	va_list args;
	va_start(args, string);
	char timeinfo[100] = "?";
	time_t ctime = time(NULL);
	struct tm * ltime = localtime(&ctime);
	
	if(ctime != -1 && ltime != NULL)
		strftime(timeinfo, 128, "%c", ltime);
		
	if(print){
		printf("ERROR - %s ", timeinfo);
		vprintf(string, args);
		printf("\"\n");	
	}
	
	if(log){
		fprintf(cgl_logfile_handle, "ERROR - %s ", timeinfo);
		vfprintf(cgl_logfile_handle, string, args);
		fprintf(cgl_logfile_handle, "\"\n");	
	}
	
}
//make everything into actual function

//add multiple window feature, activewindow?
//add viewports
//add key enums
//add pixel shit
//add image processing
//add audio 




















														
								






