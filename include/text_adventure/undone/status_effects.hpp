#ifndef STATUS_EFFECTS_H
#define STATUS_EFFECTS_H

#include <raylib-cpp.hpp>

#include <unordered_map>
#include <string>

class StatusEffectsDatabase
{
    std::unordered_map<std::string, StatusEffectInfo> definitions;

public:
    void LoadJSON();
    StatusEffectInfo &GetInfo(const std::string &effectId);
};

struct StatusEffectInfo
{
    std::string displayName;
    std::string displayDescription;
    Color displayColor;

    int baseStacks;
    bool isDebuff;
};

#endif