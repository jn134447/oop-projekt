#ifndef HELPER_H
#define HELPER_H

#include "raylib-cpp.hpp"
#include "game_constants.hpp"
#include "json.hpp"
using json = nlohmann::json;

raylib::Color LoadColorFromJSON(const json &colorData);

#endif