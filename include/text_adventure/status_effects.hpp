#ifndef STATUS_EFFECTS_H
#define STATUS_EFFECTS_H

#include <unordered_map>
#include <string>

class StatusEffects
{
    std::unordered_map<std::string, Effect> effects;
    void AddEffect(std::string &effectId,
                   const bool active = false,
                   const int strenght = 1);
    
};

class Effect
{
    bool active = false;
    int strenght;

    void modifyStrenght(const int delta);

};

#endif