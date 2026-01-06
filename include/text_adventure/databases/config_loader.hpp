#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H
#pragma once

#include <raylib-cpp.hpp>
#include <unordered_map>
#include <string>

#include "json.hpp"
using json = nlohmann::json;

class TextStyle
{
    raylib::Color color;
    float fontSize;
    unsigned short speed;

public:
    void LoadFromJSON(const json &textData, const TextStyle &fallback);

    const raylib::Color &GetColor() const;
    float GetFontSize() const;
    unsigned short GetSpeed() const;
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