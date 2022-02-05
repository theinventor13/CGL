#include <stdio.h>
#include <stdlib.h>
#include "cgl.h"

int main(int argc, char **argv){
	cgl_init_log();
	screen(1000, 1000);
	float step = 255.0f / screenheight;
	double rot = 0.0f;
	image mypic = loadimage("diatomaceous_earth_under_the_microscope.png");
	
	imagesize(mypic, 800, 800);
	imageclip(mypic, 100, 100, 100, 100);
	
	listkeys();
	
	float col = 0.0f;
	while(!cgl_update()){
		cls();
		
		col += dt * 100.0f;
		col = fmod(col, 255.0f);
		for(int i = 0; i < screenheight; i++){
			col += step;
			color(255.0f - col, col, 0);
			line(0, i, screenwidth, i);
		}
		
		if(keydown(79))
			rot += dt * 90.0f;
		
		if(keydown(80))
			rot -= dt * 90.0f;
		
		if(rot > 360.0f)
			rot -= 360.0f;
		rotateimage(mypic, rot);
		drawimage(mypic, screenwidth / 2 - mypic.w / 2, screenheight / 2 - mypic.h / 2);
		render();
	}
	
	cgl_print_error("Big problem %i, %f", 1, 1.1f);
	cgl_log_error("Big problem %i, %f", 2, 2.2f);
	cgl_lap_error("Big problem %i, %f", 3, 3.3f);
	return 0;
}




