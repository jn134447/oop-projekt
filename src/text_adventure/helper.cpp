#include "helper.hpp"

raylib::Color LoadColorFromJSON(const json &colorData)
{
    // Expects JSON array: [r, g, b, a]
    return raylib::Color(
        colorData[0].get<int>(), // Red
        colorData[1].get<int>(), // Green
        colorData[2].get<int>(), // Blue
        colorData[3].get<int>()  // Alpha
    );
}
