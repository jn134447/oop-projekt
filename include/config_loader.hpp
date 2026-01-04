#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <raylib-cpp.hpp>
#include <unordered_map>
#include <string>

struct TextStyle
{
    raylib::Color color;
    float fontSize;
    unsigned short speed;
};

class ConfigLoader
{
    TextStyle defaultTextStyle;
    std::unordered_map<std::string, TextStyle> speakers;

public:
    void LoadFromFile(const std::string &filename);
    const TextStyle &GetDefaultTextStyle() const;
    const TextStyle &GetSpeakerStyle(const std::string &speaker) const;
};

#endif