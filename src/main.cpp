#include <iostream>
#include <glib-object.h>
#include "codewar.h"

using namespace std;

int main (int argc, char** argv){
	Codewar codewar(argc, argv);
	codewar.start();
 	std::cout << "Current Page " << std::endl;
 	return 0;
}