#ifndef ITEM_LOADER_H
#define ITEM_LOADER_H
#pragma once

#include <string>
#include <unordered_map>

class ItemDefinition
{
    std::string id;
    std::string displayName;
    std::string description;

public:
    ItemDefinition(std::string id,
                   std::string displayName,
                   std::string description);
    std::string GetId() const;
    std::string GetDisplayName() const;
    std::string GetDescription() const;
};

class ItemLoader
{
    std::unordered_map<std::string, ItemDefinition> items;

public:
    void LoadFromFile(std::string &filename);
    const ItemDefinition &GetItem(const std::string &itemId) const;
    bool ItemExists(const std::string &itemId) const;
};

#endif