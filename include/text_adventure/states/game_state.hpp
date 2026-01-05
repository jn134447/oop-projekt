#ifndef GAME_STATE_H
#define GAME_STATE_H
#pragma once

#include <unordered_map>
#include <string>

// class ActiveStatusEffectInfo;
// class Stats;
// class LocationInfo;
class CharacterData;

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
    void SetFlag(const std::string &flagId);
    void ToggleFlag(const std::string &flagId);

    int GetVariable(const std::string &variableId) const;
    void SetVariable(const std::string &variableId);
    void ModifyVariable(const std::string &variableId, const int delta);

    CharacterData &currentCharacter();
    // LocationInfo &currentLocation();
};

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
    int GetItemCount(const std::string& itemId) const;
    void ClearItem(const std::string &itemId);
    void ClearAllItems();

    // void AddEffect(const std::string &effectId);
    // void ModifyEffectStack(const std::string &effectId, const int delta);
    // bool HasEffect(const std::string &effectId);
    // void ClearEffect(const std::string &effectId);
    // void ClearAllEffects();

    // Stats &StatsData();

    // void AddRelationship(const std::string &relationshipId);
    // void ChangeAffinity(const std::string &relationshipId);
    // void GetAffinity(const std::string &relationshipId);
    // void ClearAllAffinities();
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