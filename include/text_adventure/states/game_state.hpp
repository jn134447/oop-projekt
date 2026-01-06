#ifndef GAME_STATE_H
#define GAME_STATE_H
#pragma once

#include "item_loader.hpp"
#include "flag_registry.hpp"
#include "variable_registry.hpp"

#include <unordered_map>
#include <string>

class CharacterData
{
    std::unordered_map<std::string, int> inventory;

public:
    void ModifyItem(const std::string &itemId, const int quantity);
    void RemoveItem(const std::string &itemId, const int quantity);
    bool HasItem(const std::string &itemId, const int minQuantity = 1) const;
    int GetItemCount(const std::string &itemId) const;
    void ClearItem(const std::string &itemId);
    void ClearAllItems();
};
class GameState
{
    FlagRegistry &flagRegistry;
    ItemLoader &itemLoader;
    VariableRegistry &varRegistry;

    std::unordered_map<std::string, bool> currentFlags;
    std::unordered_map<std::string, int> currentVariables;

    // std::unordered_map<std::string, LocationInfo> locations;
    // std::string currentLocationId;

    // std::unordered_map<std::string, CharacterData> characters;
    CharacterData player;
    std::string currentCharacterId;

public:
    GameState(FlagRegistry &flagRegistry, ItemLoader &itemLoader, VariableRegistry &varRegistry);
    const ItemLoader &GetItemLoader() const;
    // void LoadJSON(const std::string &filename);
    // void ToJSON();

    bool GetFlag(const std::string &flagId) const;
    void SetFlag(const std::string &flagId, const bool value);
    void ToggleFlag(const std::string &flagId);
    // void LoadInitialFlags(const std::string& filename) ;

    int GetVariable(const std::string &varId) const;
    void SetVariable(const std::string &varId, const int value);
    void ModifyVariable(const std::string &varId, const int delta);

    void AddItem(const std::string &itemId, int quantity);

    CharacterData &currentCharacter();
    const CharacterData &currentCharacter() const;

    // LocationInfo &currentLocation();
};

#endif