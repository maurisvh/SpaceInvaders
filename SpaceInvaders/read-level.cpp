#include "read-level.h"
#include <string>
#include "entity.h"
#include "invader.h"
#include "shield.h"
#include "json.hpp"
#include <fstream>
#include <deque>
#include "logging.h"

const std::string levelListPath = "levels.txt";

namespace si {
	Level readLevel(std::string path) {
		info("Reading level: " + path);
		Level level;
        json j;

        std::ifstream(path) >> j;
		if (!j.is_array())
			throw std::runtime_error("invalid level object in " + path);

		for (auto &elem : j) {
			if (!elem.is_object()) {
				throw std::runtime_error("invalid object in level: " + elem.dump());
			}
			
			for (std::string &&k : { "type", "x", "y", "health" })
				if (elem.count(k) == 0)
					throw std::runtime_error("object in level lacks '" + k + "' key: " + elem.dump());

			std::string type = elem["type"];
			if (type == "invader") {
				if (elem.count("bulletPeriod") == 0)
					throw std::runtime_error("invader lacks 'bulletPeriod' key:" + elem.dump());
				level.push_back(
					std::make_shared<model::Invader>(
						sf::Vector2f(elem["x"], elem["y"]),
						elem["health"],
						sf::seconds(elem["bulletPeriod"])));
			}
			else if (type == "shield") {
				level.push_back(
					std::make_shared<model::Shield>(
						sf::Vector2f(elem["x"], elem["y"]),
						elem["health"]));
			}
		}

        return level;
    }

	std::deque<Level> readLevels() {
		std::deque<Level> levels;
		std::ifstream file(levelListPath);
		for (std::string filename; std::getline(file, filename); ) {
			filename.erase(filename.find_last_not_of("\r\n") + 1);
			if (!filename.empty())
				levels.push_back(readLevel(filename));
		}
		return levels;
	}
}

