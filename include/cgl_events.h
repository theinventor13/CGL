int cgl_newtime = 0;
int cgl_oldtime = 0;
float dt = 0.0;

int cgl_update(void){
	
	cgl_newtime = SDL_GetTicks();
	
	if(cgl_oldtime == 0)
		cgl_oldtime = cgl_newtime;
	dt = (float)(cgl_newtime - cgl_oldtime) / 1000.0;
	if(dt > 0.0){
		cgl_oldtime = cgl_newtime;
	}
	
	
	SDL_Event event;
	
	for(int i = 0; i < keycount; i++)
		keys[i].pressed = keys[i].released = false; //add array with pressed or released keys to reset
	
	
	mouse.buttons = SDL_GetMouseState(&mouse.x, &mouse.y);
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_WINDOWEVENT:
				
				break;
			case SDL_QUIT:
				
				break;
			case SDL_MOUSEBUTTONDOWN:
				
				break;
			case SDL_MOUSEBUTTONUP:
				
				break;
			case SDL_MOUSEMOTION:
				
				break;
			case SDL_KEYDOWN:
				keys[event.key.keysym.scancode].pressed = true ^ keys[event.key.keysym.scancode].status;
				keys[event.key.keysym.scancode].status = true;
				
				//event.key.keysym.sym;
				break;
			case SDL_KEYUP:
				keys[event.key.keysym.scancode].released = true & keys[event.key.keysym.scancode].status;
				keys[event.key.keysym.scancode].status = false;
				
				break;
			/*case :
				
				break;
			case :
				
				break;
			case :
				
				break;
			case :
				
				break;
			case :
				
				break;
			case :
				
				break;
			case :
				
				break;*/
		}
		if(event.type == SDL_WINDOWEVENT){
			if(event.window.event == SDL_WINDOWEVENT_CLOSE){
				return 1;
			}
		}
	}
	
	return 0;
	
}


