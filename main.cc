#include <iostream> 
#include <SDL2/SDL.h>

void f () {
	SDL_Init( SDL_INIT_EVERYTHING );
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
    SDL_Window* window = SDL_CreateWindow ( 
		"Window", 
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 
		640, 480, 
		SDL_WINDOW_SHOWN );

    SDL_Renderer* renderer = SDL_CreateRenderer( 
		window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    bool running = true;

    SDL_Rect box;
	box.w = 30;
    box.h = 30;
	box.x = 50;
    box.y = 50;
		
	float y_vel = 0;
	float gravity = 9.81;
	float time_delta = 0.1;
	bool dragging = false;

	int mouse_off_x = 0;
	int mouse_off_y = 0;
	
    while (running) {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (SDL_QUIT == ev.type) {
                running = false;
                break;
            } else if (ev.type == SDL_MOUSEBUTTONDOWN) {
				int x_mouse_pos = ev.button.x;
				int y_mouse_pos = ev.button.y;

				if (x_mouse_pos >= box.x && x_mouse_pos <= box.x + box.w &&
					y_mouse_pos >= box.y && y_mouse_pos <= box.y + box.h) {
			
					dragging = true;
					y_vel = 0;	

					mouse_off_x = x_mouse_pos - box.x;
					mouse_off_y = y_mouse_pos - box.y;
				}	
	
			} else if (ev.type == SDL_MOUSEBUTTONUP) {
				dragging = false;
			} else if (ev.type == SDL_MOUSEMOTION && dragging) {
				box.x = ev.motion.x - mouse_off_x;	
				box.y = ev.motion.y - mouse_off_y;	
			}
        }


		if (!dragging) {
			y_vel += gravity * time_delta;
			box.y += static_cast<int>(y_vel);

			if (box.y + box.h > 480) {
				box.y = 480 - box.h;
				y_vel = 0;
			}
		}

        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear (renderer);

        SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
        SDL_RenderFillRect( renderer, &box );

        SDL_RenderPresent(renderer);
		SDL_Delay(50);
    }
	return;
}

int main (void) {
	std::cout << "hello, world" << std::endl;	
	f();
	return 0;
}
