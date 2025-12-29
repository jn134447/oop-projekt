#ifndef GAME_STATE_H
#define GAME_STATE_H
#pragma once

#include <unordered_map>
#include <string>

#include "inventory.hpp"

class GameState
{
    std::unordered_map<std::string, bool> worldFlags;
    std::unordered_map<std::string, int> worldVariables;

    std::unordered_map<std::string, std::string> locations;
    std::string currentLocationId;

    std::unordered_map<std::string, CharacterData> characters;
    std::string currentCharacterId;

public:
    void LoadJSON();
    void ToJSON();

    CharacterData &currentCharacter();
    std::string &getCurrentLocationName() const;
};

class CharacterData
{
    std::unordered_map<std::string, int> inventory;
    std::unordered_map<std::string, ActiveStatusEffectInfo> effects;
    Stats stats;
    std::unordered_map<std::string, int> relationships;

public:
    void AddItem(const std::string &itemId, const int quantity);
    void RemoveItem(const std::string &itemId, const int quantity);
    void HasItem(const std::string &itemId, const int minQuantity = 1) const;
    void ClearItem(const std::string &itemId);
    void ClearAllItems();

    void AddEffect(const std::string &effectId);
    void AddEffectStack(const std::string &effectId);
    void RemoveEffectStack(const std::string &effectId);
    void ClearEffect(const std::string &effectId);
    void ClearAllEffects();

    Stats &GetStatsData();

    void AddRelationship(const std::string &relationshipId);
    void ChangeAffinity(const std::string &relationshipId);
    void GetAffinity(const std::string &relationshipId);
    void ClearAllAffinities();
};

class ActiveStatusEffectInfo
{
    std::string effectId;
    int stacks;
};

struct Stats
{
    int health;
    int stamina;
    bool isAlive;
};

#endif