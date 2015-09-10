#include "ui/window.h"
#include "codewar.h"

Codewar::Codewar(int c, char** v){
	argc = c;
	argv = v;
}

void Codewar::start(){
	Window win (&argc, &argv);
 	win.show();
}