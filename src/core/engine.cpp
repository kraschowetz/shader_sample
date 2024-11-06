#include "engine.hpp"
#include "timer.hpp"

Engine::Engine() {
	canvas = new Canvas(800, 600);
	running = false;
}

void Engine::stop() {
	delete canvas;
}

void Engine::poll_events() {
	SDL_Event e;
	SDL_PollEvent(&e);

	switch(e.type) {
		case SDL_QUIT:
			running = false;
			break;
	}
}

void Engine::start() {
	running = true;
	Timer delta_timer;
	Timer timer;
	delta_timer.start();
	timer.start();

	while(running) {
		poll_events();
		
		canvas->get_renderer()->time = (f32)(timer.get_ticks() / 1000.0);
		canvas->render();
		
		delta = (f32)(delta_timer.get_ticks() / 1000.0);
		frames++;
		delta_timer.start();

		if(timer.get_ticks() / 1000.0 >= 1.0) {
			timer.start();
			std::cout << frames << "\n";
			frames = 0;
		}
	}

	stop();
}
