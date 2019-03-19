#include "visualisation.h"
#include <string.h>

//Where it all begins
int main(int argc, char** argv) {
	
	//Setup the visualisation environment if "-v" is passed
	if(argc == 2 && (strcmp(argv[1], "-v") == 0) ) {
		setup(argc, argv);
	}
}