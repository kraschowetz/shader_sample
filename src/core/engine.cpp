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

void Engine::update() {
	
}

void Engine::start() {
	running = true;
	Timer delta_timer;
	Timer time_timer;
	delta_timer.start();
	time_timer.start();

	while(running) {
		poll_events();
		update();
		canvas->time = (f32)(time_timer.get_ticks() / 1000.0);
		canvas->render();
		
		delta = (f32)(delta_timer.get_ticks() / 1000.0);
		delta_timer.start();
	}

	stop();
}
