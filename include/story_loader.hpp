#ifndef STORY_LOADER_H
#define STORY_LOADER_H

#include <unordered_map>
#include <string>
#include "config_loader.hpp"

class StoryLoader
{
    const ConfigLoader &config;

public:
    StoryLoader(const ConfigLoader &config);

    void LoadFromFile(const std::string &filename);
};

#endif