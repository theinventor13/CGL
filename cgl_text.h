#define CGL_QUICK_TEXT 1
#define CGL_GOOD_TEXT 2


#define kerningon()							TTF_SetFontKerning(cgl_dfont, 1);
#define kerningoff()						TTF_SetFontKerning(cgl_dfont, 0);
#define text(cx, cy, string)				cgl_text(CGL_QUICK_TEXT, cx, cy, string);
#define goodtext(cx, cy, string)			cgl_text(CGL_GOOD_TEXT, cx, cy, string);
#define textf(cx, cy, string, ...)			cgl_pre_text(CGL_QUICK_TEXT, cx, cy, string, __VA_ARGS__);
#define goodtextf(cx, cy, string, ...)		cgl_pre_text(CGL_GOOD_TEXT, cx, cy, string, __VA_ARGS__);

#define cgl_pre_text(params, cx, cy, string, ...)		{sprintf(cgl_text_data, string, __VA_ARGS__); \
														cgl_text(params, cx, cy, cgl_text_data);}
														
#define loadfont(file, size)				TTF_OpenFont(file, size);

#define defaultfont()						cgl_dfont = TTF_OpenFont("arial.ttf", 36); 


TTF_Font *cgl_dfont;
char cgl_text_data[1024*1024];

void cgl_text(int params, int x, int y, const char * string){
	
	if(cgl_dfont == NULL){
		printf("Could not load font or font not loaded\n");
		return;
	}
	if(params & CGL_GOOD_TEXT){
		cgl_surface_load = TTF_RenderText_Blended(cgl_dfont, string, cgl_dcolor);
	}else{
		cgl_surface_load = TTF_RenderText_Solid(cgl_dfont, string, cgl_dcolor);
	}
		
	if(cgl_surface_load == NULL){
		printf("Could not render font\n");
		return;
	}
	printf("here\n");
	cgl_texture_load = SDL_CreateTextureFromSurface((cgl_all_windows.array[cgl_active_window_id]).renderer_handle, cgl_surface_load);
	if(cgl_texture_load == NULL){
		printf("Could not optimize font\n");
		return;
	}
	cgl_dmask.x = x;
	cgl_dmask.y = y;
	//printf("here\n");
	SDL_QueryTexture(cgl_texture_load, NULL, NULL, &(cgl_dmask.w), &(cgl_dmask.h));
	//printf("here\n");
	SDL_RenderCopy((cgl_all_windows.array[cgl_active_window_id]).renderer_handle, cgl_texture_load, NULL, &cgl_dmask);
	//printf("here\n");
	SDL_FreeSurface(cgl_surface_load);
	SDL_DestroyTexture(cgl_texture_load);
	return;		
}	

//idk what to do about this in terms of organization, its between text and images

image imagetext(const char * string){
	cgl_surface_load = TTF_RenderText_Blended(cgl_dfont, string, cgl_dcolor);
	if(cgl_surface_load == NULL){
		printf("Could not render font\n");
		cgl_image_load.image_data = NULL;
		return cgl_image_load;
	}
	cgl_image_load.image_data = SDL_CreateTextureFromSurface((cgl_all_windows.array[cgl_active_window_id]).renderer_handle, cgl_surface_load);
	if(cgl_image_load.image_data == NULL){
		printf("Could not optimize font\n");
		return cgl_image_load;
	}
	cgl_image_defaults();
	return cgl_image_load;
}
