#pragma once

#include "condition.hpp"
#include "json.hpp"

class ConditionFactory
{
public:
    static ConditionPtr CreateFromJSON(const nlohmann::json &data);
};