#include <iostream>
#include <gtk/gtk.h>
#include <glib-object.h>
#include "codewar.h"

using namespace std;

int main (int argc, char** argv){
	Codewar codewar;
	codewar.start();
 	std::cout << "Current Page " << std::endl;
 	return 0;
}