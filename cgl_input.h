typedef struct{
	bool status;
	bool pressed;
	bool released;
}cgl_key;

#define keycount 1000
cgl_key keys[keycount];

typedef struct{
	int buttons;
	int x;
	int y;
}cgl_mouse;

cgl_mouse mouse;
