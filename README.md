# Assignment 1
**Kirckpatrick Seidel Algortihm:**  
_Requirements:_ openGL (for visualisation)  
_Compilation:_  
g++ *.cpp -lglut -lGL -lGLU -std=c++11  
_Modes:_  
	1. no command line arguments: randomly generate points and find hull  
	2. -v: random generation in visual mode  
	3. -c: manually enter the points (enter points value > 1 to exit loop)  (see instructions)  
	4. -vc: option -c with visual mode  (see instructions)  
  
_Instructions:_  
For manual mode, coordinate of points need to be in [-1,1]
A point with coordinates outside this will trigger an exit (_use this to exit_) of the manual point entry function and the program will proceed with collected set of points
