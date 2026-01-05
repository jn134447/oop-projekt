#ifndef GAME_STATE_H
#define GAME_STATE_H
#pragma once

#include <unordered_map>
#include <string>

// class ActiveStatusEffectInfo;
// class Stats;
// class LocationInfo;
class CharacterData
{
    std::unordered_map<std::string, int> inventory;
    // std::unordered_map<std::string, ActiveStatusEffectInfo> effects;
    // Stats stats;
    // std::unordered_map<std::string, int> relationships;

public:
    void AddItem(const std::string &itemId, const int quantity);
    void RemoveItem(const std::string &itemId, const int quantity);
    bool HasItem(const std::string &itemId, const int minQuantity = 1) const;
    int GetItemCount(const std::string &itemId) const;
    void ClearItem(const std::string &itemId);
    void ClearAllItems();
};
class GameState
{
    std::unordered_map<std::string, bool> worldFlags;
    std::unordered_map<std::string, int> worldVariables;

    // std::unordered_map<std::string, LocationInfo> locations;
    // std::string currentLocationId;

    // std::unordered_map<std::string, CharacterData> characters;
    CharacterData player;
    std::string currentCharacterId;

public:
    // void LoadJSON(const std::string &filename);
    // void ToJSON();

    bool GetFlag(const std::string &flagId) const;
    void SetFlag(const std::string &flagId, const bool value);
    void ToggleFlag(const std::string &flagId);

    int GetVariable(const std::string &variableId) const;
    void SetVariable(const std::string &variableId);
    void ModifyVariable(const std::string &variableId, const int delta);

    CharacterData &currentCharacter();
    const CharacterData &currentCharacter() const;
    // LocationInfo &currentLocation();
};

// class ActiveStatusEffectInfo
// {
//     std::string effectId;
//     int stacks;
// };

// class Stats
// {
//     int health;
//     int stamina;
//     bool isAlive;
// };

// class LocationInfo
// {
//     std::string name;
//     bool isVisited;
// };

#endif