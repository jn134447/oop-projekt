#include "game_state.hpp"
#include "json.hpp"
#include "game_constants.hpp"

#include <fstream>
#include <iostream>

GameState::GameState(FlagRegistry &flagRegistry, ItemLoader &itemLoader, VariableRegistry &varRegistry)
    : flagRegistry(flagRegistry), itemLoader(itemLoader), varRegistry(varRegistry)
{
}

const ItemLoader &GameState::GetItemLoader() const
{
    return itemLoader;
}

bool GameState::GetFlag(const std::string &flagId) const
{
    auto it = currentFlags.find(flagId);
    if (it != currentFlags.end())
    {
        return it->second;
    }
    // Return default if not set yet
    return flagRegistry.GetDefaultValue(flagId);
}

void GameState::SetFlag(const std::string &flagId, const bool value)
{
    if (!flagRegistry.IsRegistered(flagId))
    {
        std::cerr << "WARNING: Unknown flag: " << flagId << std::endl;
    }

    std::cout << "[GameState] Added flag " << flagId << " " << value
              << std::endl;
    currentFlags[flagId] = value;
}

CharacterData &GameState::currentCharacter()
{
    return player;
}

const CharacterData &GameState::currentCharacter() const
{
    return player;
}

int GameState::GetVariable(const std::string &varId) const
{
    auto it = currentVariables.find(varId);
    if (it != currentVariables.end())
    {
        return it->second;
    }
    // Return default if not set yet
    return varRegistry.GetDefaultValue(varId);
}

void GameState::SetVariable(const std::string &varId, const int value)
{
    if (!varRegistry.IsRegistered(varId))
    {
        std::cerr << "WARNING: Setting unregistered variable: " << varId << std::endl;
    }
    currentVariables[varId] = value;
}

void GameState::ModifyVariable(const std::string &varId, const int delta)
{
    int current = GetVariable(varId);
    SetVariable(varId, current + delta);
    std::cout << "[GameState] Modifies " << varId << " " << delta
              << " (total: " << currentVariables[varId] << ")" << std::endl;
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
