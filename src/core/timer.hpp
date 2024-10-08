#ifndef TIMER_HPP
#define TIMER_HPP

#include "../util/util.hpp"

class Timer {
	private:
		u32 start_time;
	
	public:
		void start();
		u32 get_ticks();
};

#endif
