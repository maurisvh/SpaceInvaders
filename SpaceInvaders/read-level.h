#pragma once
#include <string>
#include "entity.h"
#include "json.hpp"
#include <deque>

using json = nlohmann::json;

namespace si {
	using Level = std::vector<std::shared_ptr<model::Entity>>;

	// Levels are stored in the directory `levels`, as JSON lists of entities.
	// For example:
	//
	//     [
	//         {'type': 'invader', 'x': 200, 'y': 50, 'health': 5, 'bulletPeriod': 3.0},
	//         {'type': 'shield', 'x': 200, 'y': 100, 'health': 10}
	//     ]

	/// Read a level from the given (relative) path.
	Level readLevel(std::string path);

	/// Read all levels from the paths in the level list file.
	std::deque<Level> readLevels();
}

