#include "game_state.hpp"
#include "json.hpp"
#include "game_constants.hpp"

#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>

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
    if (flagId.empty())
    {
        std::cerr << "ERROR: Empty flag ID requested" << std::endl;
        return false;
    }
    if (!flagRegistry.IsRegistered(flagId))
    {
        std::cerr << "ERROR: Requested unregistered flag: " << flagId << std::endl;
        return false;
    }

    auto it = currentFlags.find(flagId);
    if (it != currentFlags.end())
    {
        return it->second;
    }

    // Return default if not set yet
    return flagRegistry.GetDefaultValue(flagId);
}

const std::unordered_map<std::string, bool> &GameState::GetCurrentFlags() const
{
    return currentFlags;
}

const std::unordered_map<std::string, int> &GameState::GetCurrentVariables() const
{
    return currentVariables;
}

void GameState::SetFlag(const std::string &flagId, const bool value)
{
    if (flagId.empty())
    {
        std::cerr << "ERROR: Attempted to set flag with empty ID" << std::endl;
        return;
    }
    if (!flagRegistry.IsRegistered(flagId))
    {
        std::cerr << "ERROR: Attempted to set unknown flag: " << flagId << std::endl;
        return;
    }

    std::cout << "[GameState] Set flag " << flagId << " to " << value
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
    if (varId.empty())
    {
        std::cerr << "ERROR: Empty variable ID requested" << std::endl;
        return 0;
    }
    if (!varRegistry.IsRegistered(varId))
    {
        std::cerr << "ERROR: Requested unregistered variable: " << varId << std::endl;
        return 0;
    }

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
    if (varId.empty())
    {
        std::cerr << "ERROR: Attempted to set variable with empty ID" << std::endl;
        return;
    }

    if (!varRegistry.IsRegistered(varId))
    {
        std::cerr << "ERROR: Setting unregistered variable: " << varId << std::endl;
        return;
    }

    currentVariables[varId] = value;
    std::cout << "[GameState] Set variable " << varId << " to " << value << std::endl;
}

void GameState::ModifyVariable(const std::string &varId, const int delta)
{
    if (varId.empty())
    {
        std::cerr << "ERROR: Attempted to modify variable with empty ID" << std::endl;
        return;
    }

    int current = GetVariable(varId);

    // Safe overflow check (simplified version)
    if ((delta > 0 && current > INT_MAX - delta) ||
        (delta < 0 && current < INT_MIN - delta))
    {
        std::cerr << "ERROR: Arithmetic overflow/underflow modifying variable: "
                  << varId << " (current: " << current << ", delta: " << delta << ")" << std::endl;
        return;
    }

    SetVariable(varId, current + delta);
    std::cout << "[GameState] Modified " << varId << " by " << delta
              << " (total: " << currentVariables[varId] << ")" << std::endl;
}

void GameState::ModifyItem(const std::string &itemId, int delta)
{
    if (itemId.empty())
    {
        std::cerr << "ERROR: Attempted to add item with empty ID" << std::endl;
        return;
    }
    if (delta == 0)
    {
        std::cerr << "WARNING: AddItem called with delta of 0 for item: " << itemId << std::endl;
        return;
    }
    if (!itemLoader.ItemExists(itemId))
    {
        std::cerr << "ERROR: Attempted to add unknown item: " << itemId << std::endl;
        return;
    }

    player.ModifyItem(itemId, delta);
}

void CharacterData::ModifyItem(const std::string &itemId, const int delta)
{
    if (itemId.empty())
    {
        std::cerr << "ERROR: Attempted to modify item with empty ID" << std::endl;
        return;
    }
    if (delta == 0)
    {

        std::cerr << "WARNING: ModifyItem called with delta of 0 for item: " << itemId << std::endl;
        return;
    }

    // Initialize if not present
    if (inventory.find(itemId) == inventory.end())
    {
        if (delta < 0)
        {
            std::cerr << "ERROR: Cannot remove " << -delta
                      << " of item " << itemId << " (not in inventory)" << std::endl;
            return;
        }
        inventory[itemId] = 0;
    }
    // Check for overflow
    if (delta > 0 && inventory[itemId] > INT_MAX - delta)
    {
        std::cerr << "ERROR: Arithmetic overflow adding item: " << itemId << std::endl;
        return;
    }

    // Check for negative inventory (after removal)
    int newQuantity = inventory[itemId] + delta;
    if (newQuantity < 0)
    {
        inventory.erase(itemId);
    }

    inventory[itemId] += delta;
    std::cout << "[GameState] Added " << delta << " " << itemId
              << " (total: " << inventory[itemId] << ")" << std::endl;
}

bool CharacterData::HasItem(const std::string &itemId, const int minQuantity) const
{
    if (itemId.empty())
    {
        std::cerr << "ERROR: HasItem called with empty item ID" << std::endl;
        return false;
    }
    if (minQuantity < 0)
    {
        std::cerr << "ERROR: HasItem called with negative minQuantity: " << minQuantity << std::endl;
        return false;
    }

    auto it = inventory.find(itemId);
    return it != inventory.end() && it->second >= minQuantity;
}

int CharacterData::GetItemCount(const std::string &itemId) const
{
    if (itemId.empty())
    {
        std::cerr << "ERROR: GetItemCount called with empty item ID" << std::endl;
        return 0;
    }

    auto it = inventory.find(itemId);
    return it != inventory.end() ? it->second : 0;
}

const std::unordered_map<std::string, int> &CharacterData::GetInventory() const
{
    return inventory;
}

void CharacterData::ClearInventory()
{
    inventory.clear();
}
