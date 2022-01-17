
#define pointeron()							SDL_ShowCursor(SDL_ENABLE);		
#define pointeroff()						SDL_ShowCursor(SDL_DISABLE);	

#define cls()								{SDL_SetRenderDrawColor(cgl_default_window.renderer_handle, cgl_ccolor.r, cgl_ccolor.g, cgl_ccolor.b, cgl_ccolor.a);\
											SDL_RenderClear(cgl_default_window.renderer_handle);																\
											SDL_SetRenderDrawColor(cgl_default_window.renderer_handle, cgl_dcolor.r, cgl_dcolor.g, cgl_dcolor.b, cgl_dcolor.a);}	
	
#define render()							SDL_RenderPresent(cgl_default_window.renderer_handle);

#define init()								{if(SDL_Init(SDL_INIT_VIDEO) < 0)                                         \
												printf("Video could not initialize: %s\n", SDL_GetError());           \
											if(!IMG_Init(IMG_INIT_PNG))                                               \
                								printf("Image display library failed to load: %s\n", IMG_GetError()); \
                							if(TTF_Init() == -1)                                                      \
                								printf("Text display library failed to load\n");                      \
											SDL_DisableScreenSaver();}
											
											
int screenwidth;
int screenheight;

//window data type									
typedef struct{
	
	SDL_Window * window_handle;
	SDL_Renderer * renderer_handle;
	bool fullscreen;
	int w;
	int h;
	bool active;
	
}cgl_window;

//dynamic array to mainatin window list
typedef struct{
	
	cgl_window * array;	
	uint64_t dc; //delete count
	uint64_t index;
	uint64_t len;
	
}cgl_window_DA;

cgl_window_DA cgl_window_DA_make(uint64_t size){
	
	cgl_window_DA temp;
	temp.array = malloc(size * sizeof(cgl_window));
	if(temp.array == NULL){
		printf("Couldn't allocate cgl_window_DA array");
	}
	temp.dc = 0;
	temp.index = 0;
	temp.len = size;
	return temp;
	
}

int cgl_window_DA_put(cgl_window_DA * DA, cgl_window input){
	
	if(DA->dc > 0){
		DA->index = 0;
		for(; DA->index < DA->len; DA->index++){
			if(!(DA->array[DA->index]).active) break;
		}
		DA->dc--;
	}
	
	if(DA->index >= DA->len){
		DA->len *= 2;
		DA->array = realloc(DA->array, DA->len * sizeof(cgl_window));
		if(DA->array == NULL)
			return 1;
	}
	
	DA->array[DA->index] = input;
	DA->index++;
	return 0;
	
}

void cgl_window_DA_delete(cgl_window_DA * DA, uint64_t index){
	
	(DA->array[index]).active = false;
	DA->dc++;
	return;

}

void cgl_window_DA_print(cgl_window_DA DA, uint64_t index){
	//customize
	printf("%i ", DA.array[index]);
	return;
	
}

//global stuff
uint64_t cgl_active_window_id; //window currently being drawn to
cgl_window_DA cgl_all_windows; //array containing info of all windows
cgl_window cgl_default_window;

#define cgl_window_DA_get(DA, index) DA.array[index]

typedef struct{
	
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	
}cgl_color;

SDL_Color cgl_dcolor;//draw color
SDL_Color cgl_ccolor;//clear color
											
SDL_Rect cgl_rmask; //rectangular mask
SDL_Rect cgl_smask;
SDL_Rect cgl_dmask;	


void cgl_render_init(void){
	
	cgl_all_windows = cgl_window_DA_make(10);
	return;
}

cgl_window cgl_makewindow(int w, int h, const char * text, bool fullscreen){

	cgl_window new_window;
	new_window.w = w;
	new_window.h = h;
	new_window.fullscreen = fullscreen; 
	new_window.window_handle = SDL_CreateWindow(text, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, new_window.w, new_window.h, (SDL_WINDOW_FULLSCREEN & fullscreen) | SDL_WINDOW_ALLOW_HIGHDPI);
	
	if(new_window.window_handle == NULL){
		
		printf("Window could not be created: %s\n", SDL_GetError());
		
	}else{
		
		new_window.renderer_handle = SDL_CreateRenderer(new_window.window_handle, -1, SDL_RENDERER_ACCELERATED); 
		
		if(new_window.renderer_handle == NULL){
			
			new_window.renderer_handle = SDL_CreateRenderer(new_window.window_handle, -1, SDL_RENDERER_SOFTWARE);
			if(new_window.renderer_handle == NULL)
				printf("Renderer could not be created: %s\n", SDL_GetError());
			else
				printf("Accelerated renderer could not be created, falling back to software renderer\n");
				
		}else{
			
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
			SDL_SetRenderDrawBlendMode(new_window.renderer_handle, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(new_window.renderer_handle, 0, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(new_window.renderer_handle);
			//MOVE THIS
			cgl_ccolor.r = cgl_ccolor.g = cgl_ccolor.b = 0;
			cgl_ccolor.a = SDL_ALPHA_OPAQUE;
			cgl_dcolor.r = cgl_dcolor.g = cgl_dcolor.b = 255;
			cgl_dcolor.a = SDL_ALPHA_OPAQUE;
			//MOVE THIS
			
		}
	}
	
	return new_window;
	
}			

void cgl_deletewindow(uint64_t id){
	return;
}						
