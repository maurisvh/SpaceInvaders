#include "logging.h"
#include <iostream>
#include <chrono>

namespace si {
	using namespace std::chrono;
	auto programStart = system_clock::now();

	void info(const std::string &str) {
		// sf::Time t = logClock.getElapsedTime();
		duration<double> dur = system_clock::now() - programStart;
		double sec = dur.count();
		std::fprintf(stderr, "[%02d:%06.3f] %s\n", int(sec) / 60, fmod(sec, 60.0), str.c_str());
	}
}
