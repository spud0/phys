#include <iostream> 
#include <vector> 
#include <utility> 
#include <SDL2/SDL.h>

#include "./src/math.hh"

#define GRAVITY 9.81
#define TIME_DELTA 0.1

void init_render (SDL_Renderer** renderer) {

	SDL_Init (SDL_INIT_EVERYTHING);
	SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "1");
	SDL_Window* window = SDL_CreateWindow ( 
			"window", 
			SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, 
			640, 480, 
			SDL_WINDOW_SHOWN );

	*renderer = SDL_CreateRenderer( 
			window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

	return;
}

bool handle_mouse_down ( 
				 int x_mouse, int y_mouse, 
				 bool & is_dragging, 
				 std::pair<int, int>& offsets,
				 std::pair<int, int>& previous,
				 std::pair< SDL_Rect, std::pair<float, float>> & box 
				) {

	if (x_mouse >= box.first.x && x_mouse <= box.first.x + box.first.w &&
		y_mouse >= box.first.y && y_mouse <= box.first.y + box.first.h) {

			is_dragging = true;
			
			box.second.first = box.second.second = 0.f;	

			offsets.first  = x_mouse - box.first.x;
			offsets.second = y_mouse - box.first.y;
			previous.first = box.first.x;
			previous.second = box.first.y;
			return true;
		}

	return false;
}

void handle_mouse_up ( 
				 int x_mouse, int y_mouse, 
				 bool & is_dragging, 
				 std::pair<int, int>& previous, 
				 std::pair<SDL_Rect, std::pair<float, float>> & box
				) {
	
	if (is_dragging) {
		box.second.first = (box.first.x - previous.first) * 0.6;
		box.second.second = (box.first.y - previous.second) * 0.6;
		is_dragging = false;
	}

	return; 
}

void handle_mouse_motion ( 
		 const SDL_Event& ev, 
		 bool & is_dragging, 
		 std::pair<int, int>& offsets,
		 std::pair<int, int>& previous, 
		 std::pair<SDL_Rect, std::pair<float, float>> & box
		) {

	if (is_dragging) {
	
		previous.first = box.first.x;
		previous.second = box.first.y;

		box.first.x = ev.motion.x - offsets.first;
		box.first.y = ev.motion.y - offsets.second;

	}		

}


void step_simulation (
		std::pair<SDL_Rect, std::pair<float, float>> & box,
		bool& is_dragging
		) {

	if (!is_dragging) {

		box.second.second += GRAVITY * TIME_DELTA;
		box.first.y += static_cast<int>(box.second.second);
		box.first.x += static_cast<int>(box.second.first);

		if (box.first.y + box.first.h > 480) {
			box.first.y = 480 - box.first.h;
			box.second.second = -1 * box.second.second * 0.3;
			box.second.first *= 0.9;
		}

		if (box.first.y < 0) {
			box.first.y = 0;
		 	box.second.second = -1 * box.second.second * 0.3;
		}

		if (box.first.x + box.first.w > 640) {
			box.first.x = 640 - box.first.w;
			box.second.first = -1 * box.second.first *0.3;	
		}

		if (box.first.x < 0) {
			box.first.x = 0;
			box.second.first = -1 * box.second.first * 0.3;	
		}

	}
		
	return;
}


// The Physics Engine.
int main (void) {

	// Initialize the screen.
	SDL_Renderer * view = nullptr;
	init_render (&view);

	// Get the boxes ready for the screen.
	SDL_Rect box = {.x = 30, .y = 50, .w = 30, .h = 30 };
	std::vector <std::pair <SDL_Rect, std::pair <float, float>>> boxes;
	boxes.push_back(std::make_pair (box, std::make_pair(0, 0)));

	for (int i = 0; i < 4; i++) {
		boxes.push_back ({
			SDL_Rect {
				.x = 30 + i * 5,
				.y = 50 + i * 5,
				.w = 30, .h = 30
			}, 

			{0, 0}
		});
	}	
	
	bool is_dragging = false;
	bool is_running = true;

	std::pair<int, int> offsets {0, 0};
	std::pair<int, int> previous {0, 0};

	std::pair<SDL_Rect, std::pair<float, float>> * current = nullptr;

	// The main "game" loop.
	while (is_running) {
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
				case SDL_QUIT:
					is_running = false; break;
		
				case SDL_MOUSEBUTTONUP:
					if (current) {
						handle_mouse_up (ev.button.x, ev.button.y, is_dragging, previous, *current);
						current = nullptr;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:

					for (auto& box: boxes) {
						if ( handle_mouse_down(ev.button.x, ev.button.y, is_dragging, offsets, previous, box) ){
							current = &box; break;	
						}	
					}									
					break;
				case SDL_MOUSEMOTION:
					if (current) handle_mouse_motion (ev, is_dragging, offsets, previous, *current);
					break;
			}

		}

		// Update each box and render it. 
		for (auto& box: boxes) {
			step_simulation (box, is_dragging);
		}

		
		SDL_SetRenderDrawColor (view, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear (view);
		SDL_SetRenderDrawColor (view, 0xFF, 0x00, 0x00, 0xFF );

		for (const auto& box: boxes) {
			SDL_RenderFillRect(view, &box.first);
		}
			
		SDL_RenderPresent (view);
		SDL_Delay(25);

	}
	
	return 0;

}
