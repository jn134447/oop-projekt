#ifndef EFFECT_LOADER_H
#define EFFECT_LOADER_H
#pragma once

#include <string>
#include <unordered_map>

class EffectDefinition
{
    std::string id;
    std::string displayName;
    std::string description;

public:
    EffectDefinition(std::string id,
                   std::string displayName,
                   std::string description);
    const std::string &GetId() const;
    const std::string &GetDisplayName() const;
    const std::string &GetDescription() const;
};

class EffectLoader
{
    std::unordered_map<std::string, EffectDefinition> effects;

public:
    void LoadFromFile(const std::string &filename);
    const EffectDefinition &GetItem(const std::string &effectId) const;
    bool ItemExists(const std::string &effectId) const;
};

#endif