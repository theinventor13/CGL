#include <stdio.h>
#include <stdlib.h>
#include "cgl.h"

int main(int argc, char **argv){
	cgl_init_log(cgl_default_logfile);
	screen(1000, 1000);
	float step = 255.0 / screenheight;
	double rot = 0.0;
	image mypic = loadimage("diatomaceous_earth_under_the_microscope.png");
	
	imagesize(mypic, 800, 800);
	imageclip(mypic, 100, 100, 100, 100);
	while(!cgl_update()){
		cls();
		float col = 0.0;
		for(int i = 0; i < screenheight; i++){
			col += step;
			color(255.0 - col, col, 0);
			line(0, i, screenwidth, i);
		}
		
		if((rot += dt * 90) > 360.0)
			rot -= 360.0;
		rotateimage(mypic, rot);
		drawimage(mypic, screenwidth / 2 - mypic.w / 2, screenheight / 2 - mypic.h / 2);
		render();
	}
	
	cgl_print_error("Big problem %i, %f", 1, 1.1f);
	cgl_log_error("Big problem %i, %f", 2, 2.2f);
	cgl_lap_error("Big problem %i, %f", 3, 3.3f);
	return 0;
}




