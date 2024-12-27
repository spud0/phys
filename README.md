# Physics Engine #

in C++, SDL and some other goodies

# Plan #
	-  refactor using namespaces and a quadtree (rough ideas)
		- phys (constants and other physics formula's)
		- view (renderer)
		- shape (add in different classes for different shapes (`SDL_Rect` etc) 
		- ui/ux (add a key for adding and removing shapes, and make each shape added a diff color)
		- add a box with text for number of boxes, frame rate, etc (kinda like nerd-stats in yt)
		- add ability to store have multiple shapes colliding
	
	- use catch2 for testing
