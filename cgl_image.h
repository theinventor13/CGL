#define drawimage(file, cx, cy)				{file.image_transform.x = cx; \
											file.image_transform.y = cy; \
											SDL_RenderCopyEx((cgl_all_windows.array[cgl_active_window_id]).renderer_handle, file.image_data, &(file.image_clip), &(file.image_transform), file.image_rotation, NULL, file.image_flip);}
											
#define rotateimage(file, deg)				file.image_rotation = deg;

#define imagecenter(file, cx, cy)			{file.image_center.x = cx; \
											file.image_center.y = cy;}
											
#define imagehflip(file)					file.image_flip ^= SDL_FLIP_HORIZONTAL;

#define imagevflip(file)					file.image_flip ^= SDL_FLIP_VERTICAL;

#define imagesize(file, cw, ch)				{file.w = file.image_transform.w = cw; \
											file.h = file.image_transform.h = ch;}
											
#define imagescale(file, sw, sh)			{file.w = file.image_transform.w = (float)file.image_transform.w * sw; \
											file.h = file.image_transform.h = (float)file.image_transform.h * sh;}
											
#define imageclip(file, cl, cr, ct, cb)		{file.image_clip.x = cl;                          \
											file.image_clip.y = ct;                          \
											file.image_clip.w = file.image_info.w - cl - cr; \
											file.image_clip.h = file.image_info.h - ct - cb; }
																			
typedef struct{
	
	SDL_Surface * buffer_data;
	SDL_Texture * image_data;
	SDL_Rect image_info;
	SDL_Rect image_clip;
	SDL_Rect image_transform;
	double image_rotation;
	SDL_Point image_center;
	SDL_RendererFlip image_flip;
	int w;
	int h;
	bool center_change;
	
}image;	

SDL_Surface * cgl_surface_load;			
SDL_Texture * cgl_texture_load;
image cgl_image_load;

void cgl_image_defaults(){
	
	cgl_image_load.image_clip.x = cgl_image_load.image_clip.y = 0;
	SDL_QueryTexture(cgl_image_load.image_data, NULL, NULL, &(cgl_image_load.image_clip.w), &(cgl_image_load.image_clip.h));
	cgl_image_load.image_info = cgl_image_load.image_clip;
	cgl_image_load.w = cgl_image_load.image_info.w;
	cgl_image_load.h = cgl_image_load.image_info.h;
	cgl_image_load.image_transform = cgl_image_load.image_clip;
	cgl_image_load.image_rotation = 0.0;
	cgl_image_load.image_center.x = cgl_image_load.image_center.y = 0;
	cgl_image_load.image_flip = SDL_FLIP_NONE;
	return;
	
}

image loadimage(char * file){
	
	
	
	cgl_image_load.buffer_data = IMG_Load(file);
	
	if(cgl_image_load.buffer_data == NULL){
		
		cgl_lap_error("Image \"%s\" could not be loaded: %s", file, IMG_GetError());
		cgl_image_load.image_data = NULL;
		return cgl_image_load;
		
	}
	
	cgl_image_load.image_data = SDL_CreateTextureFromSurface((cgl_all_windows.array[cgl_active_window_id]).renderer_handle, cgl_image_load.buffer_data);
	
	if(cgl_image_load.image_data == NULL){
		
		cgl_lap_error("Surface \"%s\" could not be converted: %s", file, IMG_GetError());
		return cgl_image_load;
		
	}
	
	cgl_image_defaults(cgl_image_load);
	return cgl_image_load;
	
}									
