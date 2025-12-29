#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <unordered_map>
#include <string>

#include "inventory.hpp"

class GameState{
    
    std::unordered_map<std::string, bool> worldFlags;
    std::unordered_map <std::string, int> worldVariables;
    std::unordered_map<std::string, std::string> worldStrings;

    std::unordered_map<std::string, std::string> locations;
    std::string currentLocationId;

    std::unordered_map<std::string, CharacterData> characters;
    std::string currentCharacterId;

    public:
        CharacterData& currentCharacter();
        std::string& getCurrentLocationName() const;
};

class CharacterData{
    Inventory inventory;
    StatusEffects statusEffects;
    Stats stats;
    Relationship affinity;
};

#endif