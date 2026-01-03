#ifndef CONDITION_H
#define CONDITION_H

#include "game_state.hpp"
#include "json.hpp"
using json = nlohmann::json;

#include <string>

class Condition
{
    enum class Type
    {
        HAS_ITEM,
        FLAG_SET,
        VARIABLE_COMPARE,
        HAS_EFFECT,
        AFFINITY_MIN
    };

    Type type;
    std::string key;        // item_id, flag_name, variable_name, etc.
    int value;              // quantity, comparison value
    std::string comparison; // "==", ">=", "<=", etc. (for variables)

public:
    bool Evaluate(const GameState &state) const;
    static Condition FromJSON(const json &data);
};

#endif