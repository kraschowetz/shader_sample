#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "../util/util.hpp"
#include "../gfx/canvas.hpp"

class Engine {
	private:
		Canvas *canvas;
		bool running;
		f32 delta;

	public:
		Engine();
		void start();
		void stop();
		void poll_events();
};

#endif
