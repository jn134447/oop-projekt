#include "game_state.hpp"
#include "json.hpp"
#include "game_constants.hpp"

#include <fstream>
#include <iostream>

CharacterData &GameState::currentCharacter()
{
    return player;
}

const CharacterData &GameState::currentCharacter() const
{
    return player;
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
