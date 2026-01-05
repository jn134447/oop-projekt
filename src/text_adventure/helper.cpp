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

raylib::Color GetColorFromJSON(const json &colorData, const raylib::Color &fallback)
{
    if (colorData.is_array() && colorData.size() >= 3)
    {
        return raylib::Color(
            colorData[0].get<int>(),
            colorData[1].get<int>(),
            colorData[2].get<int>(),
            colorData.size() > 3 ? colorData[3].get<int>() : 255);
    }
    return fallback;
}
