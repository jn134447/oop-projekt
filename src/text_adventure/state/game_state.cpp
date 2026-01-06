#include "game_state.hpp"
#include "json.hpp"
#include "game_constants.hpp"

#include <fstream>
#include <iostream>

GameState::GameState(ItemLoader &itemLoader)
    : itemLoader(itemLoader) {}

const ItemLoader &GameState::GetItemLoader() const
{
    return itemLoader;
}

bool GameState::GetFlag(const std::string &flagId) const
{
    auto it = worldFlags.find(flagId);
    return it != worldFlags.end() && it->second;
}

void GameState::SetFlag(const std::string &flagId, const bool value)
{
    std::cout << "[GameState] Added flag " << flagId << " " << value
              << std::endl;
    worldFlags[flagId] = value;
}

CharacterData &GameState::currentCharacter()
{
    return player;
}

const CharacterData &GameState::currentCharacter() const
{
    return player;
}

void GameState::AddItem(const std::string &itemId, int quantity)
{
    if (!itemLoader.ItemExists(itemId))
    {
        std::cerr << "WARNING: Adding unknown item: " << itemId << std::endl;
    }

    player.AddItem(itemId, quantity);
}

void CharacterData::AddItem(const std::string &itemId, const int quantity)
{
    inventory[itemId] += quantity;
    std::cout << "[GameState] Added " << quantity << " " << itemId
              << " (total: " << inventory[itemId] << ")" << std::endl;
}

bool CharacterData::HasItem(const std::string &itemId, const int minQuantity) const
{
    auto it = inventory.find(itemId);
    return it != inventory.end() && it->second >= minQuantity;
}

int CharacterData::GetItemCount(const std::string &itemId) const
{
    auto it = inventory.find(itemId);
    return it != inventory.end() ? it->second : 0;
}
