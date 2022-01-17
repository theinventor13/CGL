


#define plot(x, y) 							SDL_RenderDrawPoint(cgl_default_window.renderer_handle, x, y);

#define line(x1, y1, x2, y2)				SDL_RenderDrawLine(cgl_default_window.renderer_handle, x1, y1, x2, y2);
	
#define rect(cx, cy, cw, ch) 				{cgl_rmask.x = cx;\
											cgl_rmask.y = cy; \
											cgl_rmask.w = cw; \
											cgl_rmask.h = ch; \
											SDL_RenderDrawRect(cgl_default_window.renderer_handle, &cgl_rmask);}
									
#define fillrect(cx, cy, cw, ch)			{cgl_rmask.x = cx;\
											cgl_rmask.y = cy; \
											cgl_rmask.w = cw; \
											cgl_rmask.h = ch; \
											SDL_RenderFillRect(cgl_default_window.renderer_handle, &cgl_rmask);}
											
#define triangle(x1, y1, x2, y2, x3, y3) 	{line(x1, y1, x2, y2);\
											line(x2, y2, x3, y3); \
											line(x3, y3, x1, y1);}
											

#define color(cr, cg, cb)					{cgl_dcolor.r = cr;              \
											cgl_dcolor.g = cg;               \
											cgl_dcolor.b = cb;               \
											cgl_dcolor.a = SDL_ALPHA_OPAQUE; \
											SDL_SetRenderDrawColor(cgl_default_window.renderer_handle, cgl_dcolor.r, cgl_dcolor.g, cgl_dcolor.b, cgl_dcolor.a);}//make variadic with color type
	
	
#define acolor(cr, cg, cb, ca)				{cgl_dcolor.r = cr;\
											cgl_dcolor.g = cg; \
											cgl_dcolor.b = cb; \
											cgl_dcolor.a = ca; \
											SDL_SetRenderDrawColor(cgl_default_window.renderer_handle, cgl_dcolor.r, cgl_dcolor.g, cgl_dcolor.b, cgl_dcolor.a);} //make variadic with color type
	
#define clscolor(cr, cg, cb)				{cgl_ccolor.r = cr;              \
											cgl_ccolor.g = cg;               \
											cgl_ccolor.b = cb;               \
											cgl_ccolor.a = SDL_ALPHA_OPAQUE; \
											SDL_SetRenderDrawColor(cgl_default_window.renderer_handle, cgl_ccolor.r, cgl_ccolor.g, cgl_ccolor.b, cgl_ccolor.a);} //make variadic with color type


											
											
void circle(double x, double y, double r){
	const double ival = M_PI / 4.0;
	double n = 10.0;
	double dt = ival / n;
	double px = r;
	double py = 0.0;
	double nx = r;
	double ny = 0.0;
	
	for(float pt = dt; pt < (ival + dt); pt += dt){
		nx = r * cos(pt);
		ny = r * sin(pt);
		line(x + px, y + py, x + nx, y + ny);
		line(x - px, y + py, x - nx, y + ny);
		line(x + px, y - py, x + nx, y - ny);
		line(x - px, y - py, x - nx, y - ny);
		line(x + py, y + px, x + ny, y + nx);
		line(x - py, y + px, x - ny, y + nx);
		line(x + py, y - px, x + ny, y - nx);
		line(x - py, y - px, x - ny, y - nx);
		px = nx;
		py = ny;
	}
}



void filltriangle(double x1, double y1, double x2, double y2, double x3, double y3){
	
	#define swap(x1, y1, x2, y2)	x1 += x2; y1 += y2; x2 = x1 - x2; y2 = y1 - y2; x1 -= x2; y1 -= y2;
	
	if(y2 < y1){
		swap(x1, y1, x2, y2);
	}
		
	if(y3 < y2){
		swap(x3, y3, x2, y2);
	}
	
	if(y2 < y1){
		swap(x2, y2, x1, y1);
	}
	
	#undef swap
		
	double m1 = (x2 - x1) / (y2 - y1);
	double b1 = -m1 * y1 + x1;
	double m2 = (x3 - x2) / (y3 - y2);
	double b2 = -m2 * y2 + x2;
	double m3 = (x3 - x1) / (y3 - y1);
	double b3 = -m3 * y3 + x3;
	
	if(y1 == y3){
		line(x1, y1, x2, y2); line(x2, y2, x3, y3);
		return;
	}
	
	if(y1 != y2)
		for(double i = y1; i < y2; i++)
			line(m1 * i + b1, i, m3 * i + b3, i);
	
	for(double i = y2; i < y3; i++)
		line(m2 * i + b2, i, m3 * i + b3, i);
	
	return;
}

/*
cgl_loadaudio();
cgl_drawbezier();
cgl_fillcircle();
cgl_drawtext();
cgl_playaudio();
*/
	
