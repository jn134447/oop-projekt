#include "item_loader.hpp"
#include <stdexcept>
#include <unordered_map>

ItemDefinition::ItemDefinition(std::string id, std::string displayName, std::string description)
    : id(id), displayName(displayName), description(description) {}

std::string ItemDefinition::GetId() const
{
    return id;
}

std::string ItemDefinition::GetDisplayName() const
{
    return displayName;
}

std::string ItemDefinition::GetDescription() const
{
    return description;
}

void ItemLoader::LoadFromFile(std::string &filename)
{
}

const ItemDefinition &ItemLoader::GetItem(const std::string &itemId) const
{
    auto it = items.find(itemId);
    if (it == items.end())
    {
        throw std::runtime_error("Unknown item: " + itemId);
    }
    return it->second;
}

bool ItemLoader::ItemExists(const std::string &itemId) const
{
    return items.find(itemId) != items.end();
}
